#pragma once
#include <glm.hpp>

class Grid
{
public:
	Grid(int xCells, int zCells, float cellSize, glm::vec3 origin = glm::vec3(0.0f));
	void draw();
private:
	unsigned int vertexBuffer;
	unsigned int vertexArray;
	int m_lines = 0;
};

