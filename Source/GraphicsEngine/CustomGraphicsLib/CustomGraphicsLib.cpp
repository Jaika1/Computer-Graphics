#include "pch.h"
#include "CustomGraphicsLib.h"
#include <iostream>
#include <gl/glew.h>
#include <glfw3.h>

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

bool GLInitWindow(const char* title, int width, int height)
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
		GLCloseWindow();
		return false;
	}

	glEnable(GL_DEPTH_TEST); // Enable the depth buffer
	std::cout << glGetString(GL_VERSION) << std::endl;

	return true;
}

bool GLWindowShouldClose() {
	// Be safe and check to see if the window even exists!
	if (!windowPointer) return false;
	return glfwWindowShouldClose(windowPointer);
}

void GLCloseWindow()
{
	// Be safe and check to see if the window even exists!
	if (windowPointer)
	{
		glfwDestroyWindow(windowPointer);
		glfwTerminate();
	}
}

void GLSwapBuffers()
{
	// Be safe and check to see if the window even exists!
	if (windowPointer)
		glfwSwapBuffers(windowPointer);
}

void GLPollEvents()
{
	glfwPollEvents();
}

void GLClearColour(float red, float green, float blue, float alpha)
{
	glClearColor(red, green, blue, alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLDrawTriangle2D(glm::vec2 pos1, glm::vec2 pos2, glm::vec2 pos3, glm::vec4 colour)
{
	glBegin(GL_TRIANGLES);
	glColor4f(colour.r, colour.g, colour.b, colour.a);
	glVertex2f(pos1.x, pos1.y);
	glVertex2f(pos2.x, pos2.y);
	glVertex2f(pos3.x, pos3.y);
	glEnd();
}

void GLDrawQuad2D(glm::vec2 pos1, glm::vec2 pos2, glm::vec2 pos3, glm::vec2 pos4, glm::vec4 colour)
{
	GLDrawTriangle2D(pos3, pos1, pos2, colour);
	GLDrawTriangle2D(pos3, pos4, pos2, colour);
}