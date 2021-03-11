#include "Grid.h"
#include "gl46.h"

Grid::Grid(int xCells, int zCells, float cellSize, glm::vec3 origin)
{
	float* verts = new float[(xCells + zCells) * 6];

	for (int x = 0; x < xCells; ++x)
	{
		verts[(x * 6) + 0] = (x * cellSize) - (((float)xCells * cellSize) / 2.0f) + origin.x;
		verts[(x * 6) + 1] = origin.y;
		verts[(x * 6) + 2] = -(((float)zCells * cellSize) / 2.0f) + origin.z;

		verts[(x * 6) + 3] = (x * cellSize) - (((float)xCells * cellSize) / 2.0f) + origin.x;
		verts[(x * 6) + 4] = origin.y;
		verts[(x * 6) + 5] = (((float)zCells * cellSize) / 2.0f) + origin.z;
	}

	for (int z = 0; z < zCells; ++z)
	{
		verts[(xCells * 6) + (z * 6) + 0] = -(((float)xCells * cellSize) / 2.0f) + origin.x;
		verts[(xCells * 6) + (z * 6) + 1] = origin.y;
		verts[(xCells * 6) + (z * 6) + 2] = (z * cellSize) - (((float)zCells * cellSize) / 2.0f) + origin.z;

		verts[(xCells * 6) + (z * 6) + 3] = (((float)xCells * cellSize) / 2.0f) + origin.x;
		verts[(xCells * 6) + (z * 6) + 4] = origin.y;
		verts[(xCells * 6) + (z * 6) + 5] = (z * cellSize) - (((float)zCells * cellSize) / 2.0f) + origin.z;
	}

	// Create a vertex buffer and a vertex array
	glCreateBuffers(1, &vertexBuffer);
	glCreateVertexArrays(1, &vertexArray);

	// Bind the vertex buffer and array
	glBindVertexArray(vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	glBufferData(GL_ARRAY_BUFFER, (xCells + zCells) * 6 * sizeof(float), verts, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	m_lines = (xCells + zCells) * 2;
	delete[] verts;
}

void Grid::draw()
{
	glBindVertexArray(vertexArray);
	glDrawArrays(GL_LINES, 0, m_lines);
}