#include "gl46.h"
#include <glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "Grid.h"
#include "Plane.h"
#include "OBJMesh.h"

unsigned int CreateShader(unsigned int type, const char* source)
{
	unsigned int sid = glCreateShader(type);
	glShaderSource(sid, 1, &source, nullptr);
	glCompileShader(sid);

	int cStat;
	glGetShaderiv(sid, GL_COMPILE_STATUS, &cStat);
	if (cStat == GL_FALSE)
	{
		int logLength;
		glGetShaderiv(sid, GL_INFO_LOG_LENGTH, &logLength);
		char* log = new char[logLength];
		glGetShaderInfoLog(sid, logLength, &logLength, log);

		std::cout << "Compiling shader of type " << type << " failed!" << std::endl;
		std::cout << log << std::endl;

		delete[] log;
		return 0;
	}

	return sid;
}

int main()
{
	unsigned int buffer;
	unsigned int program;
	unsigned int vertexArray;
	glm::mat4 projection = glm::perspective(1.3f, 16.0f / 9.0f, 0.1f, 150.0f);
	glm::mat4 viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -5.0f, -14.0f));

	if (glfwInit() == GLFW_FALSE)
		return -1;

	GLFWwindow* window = glfwCreateWindow(1600, 900, "OpenGL Window", nullptr, nullptr);

	if (!window)
	{
		glfwTerminate();
		return -2;
	}

	glfwMakeContextCurrent(window);

	if (!glfwGetCurrentContext())
	{
		glfwTerminate();
		return -3;
	}

	glEnable(GL_DEPTH_TEST);

	std::ifstream vertexShaderFS("./shaders/shader.vert");
	std::ifstream fragmentShaderFS("./shaders/shader.frag");

	std::string vertexShaderString = std::string(std::istreambuf_iterator<char>(vertexShaderFS), std::istreambuf_iterator<char>());
	std::string fragmentShaderString = std::string(std::istreambuf_iterator<char>(fragmentShaderFS), std::istreambuf_iterator<char>());

	const char* vertexShaderSource = vertexShaderString.c_str();
	const char* fragmentShaderSource = fragmentShaderString.c_str();

	unsigned int vs = CreateShader(GL_VERTEX_SHADER, vertexShaderSource);
	unsigned int fs = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

#pragma region Creating a shader program and linking it, along with a validation check.
	program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);

	int vStat;
	glGetProgramiv(program, GL_LINK_STATUS, &vStat);
	if (vStat == GL_FALSE)
	{
		int logLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
		char* log = new char[logLength];
		glGetProgramInfoLog(program, logLength, &logLength, log);

		std::cout << "Shader program failed to link!" << std::endl;
		std::cout << log << std::endl;

		delete[] log;
	}

	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);
	glUseProgram(program);
#pragma endregion

	Grid g(50, 50, 1.0f, glm::vec3(0.0f, -1.0f, 0.0f));
	Plane p(2.0f, 4.0f, glm::vec3(0.0f, -1.0f, -6.0f));
	aie::OBJMesh m;
	m.load("mod/bunny.obj", false);
	

	/*glGenBuffers(1, &buffer);
	glGenVertexArrays(1, &vertexArray);

	glBindVertexArray(vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	float verts[9]
	{
		-0.5f, -0.5f, -10.0f,
		 0.0f,  0.5f, -10.0f,
		 0.5f, -0.5f, -10.0f,
	};
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), verts, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);*/

	while (glfwWindowShouldClose(window) == GLFW_FALSE)
	{
		glClearColor(0.05f, 0.05f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUniformMatrix4fv(glGetUniformLocation(program, "ProjectionCanvas"), 1, GL_FALSE, &projection[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(program, "ViewMatrix"), 1, GL_FALSE, &viewMatrix[0][0]);
		/*glDrawArrays(GL_TRIANGLES, 0, 3);*/
		p.draw();
		m.draw();
		g.draw();
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteProgram(program);
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}