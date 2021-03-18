#include "pch.h"
#include "WindowFunctions.h"
#include <iostream>
#include <gl/glew.h>
#include <glfw/glfw3.h>


extern GLFWwindow* g_gameWindow = nullptr;

extern float g_deltaTime = 0.0f;

extern clock_t g_timer = clock();


bool JGL_InitializeWindow(const char* title, int width, int height)
{
	if (glfwInit() == GLFW_FALSE)
	{
		std::cout << "Failed to initialize GLFW!" << std::endl;
		return false;
	}

	g_gameWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);

	if (g_gameWindow == nullptr)
	{
		std::cout << "Failed to initialize the window!" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(g_gameWindow);

	if (!glfwGetCurrentContext())
	{
		std::cout << "Failed to make context from the initialized window!" << std::endl;
		glfwDestroyWindow(g_gameWindow);
		glfwTerminate();
		g_gameWindow = nullptr;
		return false;
	}

	glewInit();

	std::cout << "Vendor:   " << glGetString(GL_VENDOR) << std::endl
		      << "Version:  " << glGetString(GL_VERSION) << std::endl
		      << "GLSL Ver: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	return true;
}

void JGL_DestroyWindow()
{
	glfwDestroyWindow(g_gameWindow);
	glfwTerminate();
	g_gameWindow = nullptr;
}

bool JGL_ShouldWindowClose()
{
	return glfwWindowShouldClose(g_gameWindow);
}

void JGL_EndDraw()
{
	glfwSwapBuffers(g_gameWindow);
	glfwPollEvents();
	g_deltaTime = (float)(clock() - g_timer) / CLOCKS_PER_SEC;
	g_timer = clock();
}

float JGL_GetDeltaTime()
{
	return g_deltaTime;
}

void JGL_ClearBackBuffer(vec4 colour)
{
	glClearColor(colour.x, colour.y, colour.z, colour.w);
	glClear(GL_COLOR_BUFFER_BIT);
}
