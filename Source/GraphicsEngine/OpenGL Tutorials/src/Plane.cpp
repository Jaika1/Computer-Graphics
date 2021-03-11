#include "Plane.h"
#include "gl46.h"

Plane::Plane(float width, float depth, glm::vec3 origin)
{
	float verts[12]
	{
		origin.x - (width / 2.0f), origin.y, origin.z - (depth / 2.0f),
		origin.x + (width / 2.0f), origin.y, origin.z - (depth / 2.0f),
		origin.x + (width / 2.0f), origin.y, origin.z + (depth / 2.0f),
		origin.x - (width / 2.0f), origin.y, origin.z + (depth / 2.0f),
	};

	glGenBuffers(1, &vertexBuffer);
	glGenVertexArrays(1, &vertexArray);

	glBindVertexArray(vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), verts, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Plane::draw()
{
	glBindVertexArray(vertexArray);
	glDrawArrays(GL_QUADS, 0, 4);
}
