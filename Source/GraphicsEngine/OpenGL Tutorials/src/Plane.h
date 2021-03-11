#pragma once
#include <glm.hpp>

class Plane
{
public:
	Plane(float width, float depth, glm::vec3 origin = glm::vec3(0.0f));
	void draw();
private:
	unsigned int vertexBuffer;
	unsigned int vertexArray;
};