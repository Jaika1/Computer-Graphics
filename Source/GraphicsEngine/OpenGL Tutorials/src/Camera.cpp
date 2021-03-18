#include "Camera.h"
#include <ext\matrix_transform.hpp>
#include <ext\matrix_clip_space.hpp>
#include "gl46.h";
#include <glfw3.h>

Camera::Camera(glm::vec3 pos) : m_theta(0.0f), m_phi(0.0f), m_position(pos) {}

glm::mat4 Camera::getProjectionMatrix()
{
	return glm::perspective(glm::pi<float>() * 0.5f, 16.0f / 9.0f, 0.1f, 250.0f);
}

glm::mat4 Camera::getViewMatrix()
{
	/*float thetaR = glm::radians(m_theta);
	float phiR = glm::radians(m_phi);
	glm::vec3 forward(cosf(phiR) * cosf(thetaR), sinf(phiR), cosf(phiR) * sinf(thetaR));*/
	return glm::lookAt(m_position, m_position + GetForwardVector(), glm::vec3(0, 1, 0));
}

glm::vec3 Camera::GetForwardVector()
{
	float thetaR = glm::radians(m_theta);
	float phiR = glm::radians(m_phi);
	return glm::vec3(cosf(phiR) * cosf(thetaR), sinf(phiR), cosf(phiR) * sinf(thetaR));
}

void Camera::UpdateCamera(GLFWwindow* window)
{
	float rate = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) ? 0.4f : 0.1f;
	const float turnSpeed = 0.1f;

	float thetaR = glm::radians(m_theta);
	float phiR = glm::radians(m_phi);

	glm::vec3 forward(cos(phiR)*cos(thetaR), sin(phiR), cos(phiR)*sin(thetaR));
	glm::vec3 right(-sin(thetaR), 0, cos(thetaR));
	glm::vec3 up(0, 1, 0);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		m_position += forward * rate;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		m_position -= forward * rate;

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		m_position -= right * rate;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		m_position += right * rate;

	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		m_position -= up * rate;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		m_position += up * rate;

	double mxd;
	double myd;
	glfwGetCursorPos(window, &mxd, &myd);
	float mx = (float)mxd;
	float my = (float)myd;

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		m_theta += turnSpeed * (mx - m_lastMouseX);
		m_phi -= turnSpeed * (my - m_lastMouseY);
	}

	m_lastMouseX = mx;
	m_lastMouseY = my;
}
