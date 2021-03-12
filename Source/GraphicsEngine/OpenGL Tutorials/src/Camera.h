#pragma once
#include <glm.hpp>

struct GLFWwindow;

class Camera
{
public:
	Camera(glm::vec3 pos = glm::vec3(0.0f));
	glm::mat4 getProjectionMatrix();
	glm::mat4 getViewMatrix();
	void UpdateCamera(GLFWwindow* window);
private:
	float m_lastMouseX;
	float m_lastMouseY;

	float m_theta;
	float m_phi;
	glm::vec3 m_position;
};

