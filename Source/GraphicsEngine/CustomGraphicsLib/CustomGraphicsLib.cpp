#include "pch.h"
#include "CustomGraphicsLib.h"
#include <iostream>
#include <gl/glew.h>
#include <glfw3.h>
#include <string>
#include <gtx/transform.hpp>

constexpr char VT_ESC = 0x1B;


GLFWwindow* windowPointer = nullptr;

unsigned int triangleBuffer = 0;
unsigned int triangleArray = 0;
glm::mat4 projMatrix(1.0f);

//unsigned int vertexBufferLength = 0;
unsigned int lastShaderProgramID = 0;


void PrintHello(bool fancy)
{
	if (!fancy)
		std::cout << "Hello World!" << std::endl;
	else
	{
		char text[] = "Hello World!";
		for (int i = 0; i < sizeof(text); ++i)
			std::cout << VT_ESC << "[38;2;0;" << (150 + (i * (105 / sizeof(text)))) << ";255m" << text[i];
		std::cout << std::endl;
	}
}

bool TryEnableCVTS()
{
	HANDLE outHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	if (outHandle == INVALID_HANDLE_VALUE)
		return false;

	DWORD consoleFlags;
	if (!GetConsoleMode(outHandle, &consoleFlags))
		return false;

	consoleFlags |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	if (!SetConsoleMode(outHandle, consoleFlags))
		return false;

	return true;
}

bool CGLInitWindow(const char* title, int width, int height)
{
	//Initialize the GLFW library.
	if (glfwInit() == false)
		return false;

	// Attempt to create a window with the specified parameters.
	windowPointer = glfwCreateWindow(width, height, title, nullptr, nullptr);

	if (windowPointer == nullptr)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(windowPointer);

	if (glewInit() != GLEW_OK)
	{
		CGLCloseWindow();
		return false;
	}

	glEnable(GL_DEPTH_TEST); // Enable the depth buffer

	glGenBuffers(1, &triangleBuffer);
	glGenVertexArrays(1, &triangleArray);

	glBindVertexArray(triangleArray);
	glBindBuffer(GL_ARRAY_BUFFER, triangleBuffer);

	// Triangle buffer.
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

	// Unbind the vertex buffer.
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	std::cout << glGetString(GL_VERSION) << std::endl;
	return true;
}

bool CGLWindowShouldClose() {
	// Be safe and check to see if the window even exists!
	if (!windowPointer) return false;
	return glfwWindowShouldClose(windowPointer);
}

void CGLCloseWindow()
{
	// Be safe and check to see if the window even exists!
	if (windowPointer)
	{
		glfwDestroyWindow(windowPointer);
		glfwTerminate();
		if (lastShaderProgramID) glDeleteProgram(lastShaderProgramID);
	}
}

void CGLSwapBuffers()
{
	// Be safe and check to see if the window even exists!
	if (windowPointer)
		glfwSwapBuffers(windowPointer);
	glUniformMatrix4fv(0, 1, GL_FALSE, &projMatrix[0][0]);
}

void CGLPollEvents()
{
	glfwPollEvents();
}

void CGLClearColour(float red, float green, float blue, float alpha)
{
	glClearColor(red, green, blue, alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void CGLDrawTriangle2D(glm::vec2 pos1, glm::vec2 pos2, glm::vec2 pos3, glm::vec4 colour)
{
	glBegin(GL_TRIANGLES);
	glColor4f(colour.r, colour.g, colour.b, colour.a);
	glVertex2f(pos1.x, pos1.y);
	glVertex2f(pos2.x, pos2.y);
	glVertex2f(pos3.x, pos3.y);
	glEnd();
}

void CGLDrawQuad2D(glm::vec2 pos1, glm::vec2 pos2, glm::vec2 pos3, glm::vec2 pos4, glm::vec4 colour)
{
	glBegin(GL_QUADS);
	glColor4f(colour.r, colour.g, colour.b, colour.a);
	glVertex2f(pos1.x, pos1.y);
	glVertex2f(pos2.x, pos2.y);
	glVertex2f(pos3.x, pos3.y);
	glVertex2f(pos4.x, pos4.y);
	glEnd();
}

unsigned int CGLCompileShader(unsigned int type, const char* source)
{
	unsigned int id = glCreateShader(type); // Create a shader object and return its ID.
	glShaderSource(id, 1, &source, nullptr); // Sets the source code to be compiled for this given shader. We are passing in only one string, so count is 1. Since this string is null-terminated, length is nullptr.
	glCompileShader(id); // Attempts to compile our shader.

	int compileStatus;
	glGetShaderiv(id, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus == GL_FALSE)
	{
		int logLength;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLength);
		char* log = new char[logLength];
		glGetShaderInfoLog(id, logLength, &logLength, log);

		std::cout << "An error occurred while compiling a shader of type " << type << "!" << std::endl;
		std::cout << log << std::endl;

		delete[] log;
		return 0;
	}

	return id;
}

unsigned int CGLMakeShaderProgramVF(const char* vertexShaderSource, const char* fragmentShaderSource)
{
	unsigned int pid = glCreateProgram();
	unsigned int vt = CGLCompileShader(GL_VERTEX_SHADER, vertexShaderSource);
	unsigned int fg = CGLCompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

	glAttachShader(pid, vt);
	glAttachShader(pid, fg);

	glLinkProgram(pid);

	int linkCode;
	glGetProgramiv(pid, GL_LINK_STATUS, &linkCode);
	if (linkCode == GL_FALSE)
	{
		int logLength;
		glGetProgramiv(pid, GL_INFO_LOG_LENGTH, &logLength);
		char* log = new char[logLength];
		glGetProgramInfoLog(pid, logLength, &logLength, log);

		std::cout << "Shader program failed to link!" << std::endl;
		std::cout << log << std::endl;

		delete[] log;
		glDeleteShader(vt);
		glDeleteShader(fg);
		glDeleteProgram(pid);

		return 0;
	}


	glValidateProgram(pid);

	int validationCode;
	glGetProgramiv(pid, GL_VALIDATE_STATUS, &validationCode);
	if (validationCode == GL_FALSE)
	{
		int logLength;
		glGetProgramiv(pid, GL_INFO_LOG_LENGTH, &logLength);
		char* log = new char[logLength];
		glGetProgramInfoLog(pid, logLength, &logLength, log);

		std::cout << "Shader program failed to validate!" << std::endl;
		std::cout << log << std::endl;

		delete[] log;
		glDeleteShader(vt);
		glDeleteShader(fg);
		glDeleteProgram(pid);

		return 0;
	}


	glDeleteShader(vt);
	glDeleteShader(fg);

	lastShaderProgramID = pid;
	glUseProgram(lastShaderProgramID);

	return pid;
}

void CGLAddTriangle2D(glm::vec2 pos1, glm::vec2 pos2, glm::vec2 pos3, glm::vec4 colour)
{
	float verticies[9]
	{
		pos1.x, pos1.y, 0.0f,
		pos2.x, pos2.y, 0.0f,
		pos3.x, pos3.y, 0.0f,
	};
	glBindVertexArray(triangleArray);
	glBindBuffer(GL_ARRAY_BUFFER, triangleBuffer);

	// Write our triangle to the buffers and draw it.
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), verticies, GL_STATIC_DRAW);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	// Unbind the vertex buffer.
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void CGLDoRender()
{
	//std::cout << "Prog: " << lastShaderProgramID << " | VertexCount: " << vertexBufferLength << std::endl;

	//glUseProgram(lastShaderProgramID);
	//glBindVertexArray(vertexArray);

	// Draw the verticies contained in the vertex buffer.
	//glDrawArrays(GL_TRIANGLES, 0, vertexBufferLength);

	//glUseProgram(0);
	//glBindVertexArray(0);

	CGLSwapBuffers();
	CGLPollEvents();
}