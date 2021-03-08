#include "gl44.h"
#include <glfw3.h>

int main()
{
	if (glfwInit() == false)
		return false;

	GLFWwindow* window = glfwCreateWindow(1280, 720, "Yes", nullptr, nullptr);

	if (window == nullptr)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);



	glfwDestroyWindow(window);
	glfwTerminate();
}