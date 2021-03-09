#include "pch.h"
#include "CustomGraphicsLib.h"
#include <iostream>
#include <gl/glew.h>
#include <glfw3.h>
#include <string>

constexpr char VT_ESC = 0x1B;


GLFWwindow* windowPointer = nullptr;


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
	}
}

void CGLSwapBuffers()
{
	// Be safe and check to see if the window even exists!
	if (windowPointer)
		glfwSwapBuffers(windowPointer);
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

		std::cout << "An error occurred while compiling a shader of type " << glGetString(type) << "!" << std::endl;
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


}