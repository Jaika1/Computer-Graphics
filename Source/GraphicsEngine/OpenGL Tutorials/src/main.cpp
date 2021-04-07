#define MAX_LIGHTS 4

#include "gl46.h"
#include <glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Grid.h"
#include "Plane.h"
#include "Camera.h"
#include "OBJMesh.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <time.h>


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

unsigned int GenShaderProgram(const char* vertSourceDir, const char* fragSourceDir)
{
	unsigned int pid;

	std::ifstream vertexShaderFS(vertSourceDir);
	std::ifstream fragmentShaderFS(fragSourceDir);

	std::string vertexShaderString = std::string(std::istreambuf_iterator<char>(vertexShaderFS), std::istreambuf_iterator<char>());
	std::string fragmentShaderString = std::string(std::istreambuf_iterator<char>(fragmentShaderFS), std::istreambuf_iterator<char>());

	const char* vertexShaderSource = vertexShaderString.c_str();
	const char* fragmentShaderSource = fragmentShaderString.c_str();

	unsigned int vs = CreateShader(GL_VERTEX_SHADER, vertexShaderSource);
	unsigned int fs = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
	
	if (vs == 0 || fs == 0) return 0;

	pid = glCreateProgram();
	glAttachShader(pid, vs);
	glAttachShader(pid, fs);
	glLinkProgram(pid);

	int vStat;
	glGetProgramiv(pid, GL_LINK_STATUS, &vStat);
	if (vStat == GL_FALSE)
	{
		int logLength;
		glGetProgramiv(pid, GL_INFO_LOG_LENGTH, &logLength);
		char* log = new char[logLength];
		glGetProgramInfoLog(pid, logLength, &logLength, log);

		std::cout << "Shader program failed to link!" << std::endl;
		std::cout << log << std::endl;

		delete[] log;

		glDeleteProgram(pid);
		glDeleteShader(vs);
		glDeleteShader(fs);

		return 0;
	}

	glValidateProgram(pid);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return pid;
}

int main()
{
	unsigned int litPid;
	unsigned int unlitPid;

	unsigned int buffer;
	unsigned int vertexArray;

	clock_t lastTime = clock();
	float deltaTime = 0.0f;

	Camera cam(glm::vec3(-15.0f, 5.0f, 0.0f));
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	glm::vec3 forwardLightDir = glm::normalize(glm::vec3(1.0f, 0.0f, -1.0f));
	glm::vec3 pointLights[4];

	pointLights[0] = glm::vec3(0.0f, -0.2f, 0.0f);
	pointLights[1] = glm::vec3(-1.0f, 2.0f, -1.0f);
	pointLights[2] = glm::vec3(-1.0f, 4.4f, 1.0f);
	pointLights[3] = glm::vec3(-1.0f, 7.3f, -1.5f);

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
	
	ImGui::CreateContext();
	//ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsLight();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");

	glEnable(GL_DEPTH_TEST);

	litPid = GenShaderProgram("./shaders/lit.vert", "./shaders/lit.frag");
	unlitPid = GenShaderProgram("./shaders/unlit.vert", "./shaders/unlit.frag");

	Grid g(50, 50, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));
	//Plane p(2.0f, 4.0f, glm::vec3(0.0f, -1.0f, -6.0f));
	aie::OBJMesh m;
	m.load("mod/soulspear/soulspear.obj", true, true);
	float warpTime = 0.0f;
	while (glfwWindowShouldClose(window) == GLFW_FALSE)
	{
		clock_t currentTime = clock();
		deltaTime = ((float)(currentTime - lastTime)) / CLOCKS_PER_SEC;

		forwardLightDir = cam.GetForwardVector();
		cam.UpdateCamera(window);

		glClearColor(0.05f, 0.05f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

#pragma region Lit Shader

		glUseProgram(litPid);

		glUniformMatrix4fv(glGetUniformLocation(litPid, "ProjectionCanvas"), 1, GL_FALSE, glm::value_ptr(cam.getProjectionMatrix()));
		glUniformMatrix4fv(glGetUniformLocation(litPid, "ViewMatrix"), 1, GL_FALSE, glm::value_ptr(cam.getViewMatrix()));
		glUniformMatrix4fv(glGetUniformLocation(litPid, "ModelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));

		glUniform4fv(glGetUniformLocation(litPid, "CameraPosition"), 1, glm::value_ptr(glm::vec3(glm::inverse(cam.getViewMatrix())[3])));
		glUniform3fv(glGetUniformLocation(litPid, "LightDirection"), 1, glm::value_ptr(forwardLightDir));

		glUniform1i(glGetUniformLocation(litPid, "numLights"), sizeof(pointLights) / sizeof(glm::vec3));
		glUniform3fv(glGetUniformLocation(litPid, "PointLightPosition"), sizeof(pointLights) / sizeof(glm::vec3), glm::value_ptr(pointLights[0]));
		//glUniform3fv(glGetUniformLocation(litPid, "PointLightColour"), pointLights.size() * 3, glm::value_ptr(forwardLightDir));

		glUniform1i(glGetUniformLocation(litPid, "diffuseTexture"), 0);
		glUniform1i(glGetUniformLocation(litPid, "specularTexture"), 1);

#pragma endregion

		m.draw();

#pragma region Unlit Shader

		glUseProgram(unlitPid);

		glUniformMatrix4fv(glGetUniformLocation(unlitPid, "ProjectionCanvas"), 1, GL_FALSE, glm::value_ptr(cam.getProjectionMatrix()));
		glUniformMatrix4fv(glGetUniformLocation(unlitPid, "ViewMatrix"), 1, GL_FALSE, glm::value_ptr(cam.getViewMatrix()));
		glUniformMatrix4fv(glGetUniformLocation(unlitPid, "ModelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));

		glUniform4fv(glGetUniformLocation(unlitPid, "BaseColour"), 1, glm::value_ptr(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));

#pragma endregion

		g.draw();

		glfwPollEvents();

#pragma region ImGui

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Directional Light Editor");
		ImGui::SliderFloat("Light Angle X", &forwardLightDir[0], -1.0f, 1.0f);
		ImGui::SliderFloat("Light Angle Y", &forwardLightDir[1], -1.0f, 1.0f);
		ImGui::SliderFloat("Light Angle Z", &forwardLightDir[2], -1.0f, 1.0f);
		ImGui::End();

		for (int i = 0; i < sizeof(pointLights) / sizeof(glm::vec3); ++i)
		{
			ImGui::Begin((std::string("Point Light Editor (") + std::to_string(i) + std::string(")")).c_str());
			ImGui::SliderFloat("Light Pos X", &pointLights[i].x, -20.0f, 20.0f);
			ImGui::SliderFloat("Light Pos Y", &pointLights[i].y, -5.0f, 20.0f);
			ImGui::SliderFloat("Light Pos Z", &pointLights[i].z, -20.0f, 20.0f);
			ImGui::End();
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

#pragma endregion

		glfwSwapBuffers(window);

		lastTime = currentTime;
	}

	glDeleteProgram(litPid);
	glDeleteProgram(unlitPid);
	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}