#include "Quad.h"
#include "Utils.h"

Quad::Quad()
{
	std::vector<glm::vec3> vertices
	{
		glm::vec3(0.5f,   0.5f, 0.0f),	// Top Right
		glm::vec3(0.5f,  -0.5f, 0.0f),	// Bottom Right
		glm::vec3(-0.5f, -0.5f, 0.0f),	// Bottom Left
		glm::vec3(-0.5f,  0.5f, 0.0f),	// Top Left
	};

	std::vector<glm::vec3> normals
	{
		glm::vec3(0, 1, 1),
		glm::vec3(1, 0, 1),
		glm::vec3(1, 0, 0),
		glm::vec3(0, 1, 0)
	};

	std::vector<glm::vec2> textureCoords
	{
		glm::vec2(0.0f, 0.0f),
		glm::vec2(0.0f, 1.f),
		glm::vec2(1.f, 1.f),
		glm::vec2(1.f, 0.f)

	};

	std::vector<unsigned short> indices =
	{
		0, 1, 3,
		1, 2, 3
	};

	quad = new Mesh("quad");
	quad->InitFromData(vertices, normals, textureCoords, indices);
}

Quad::~Quad()
{
	delete this->quad;
}

Mesh* Quad::getQuad()
{
	return this->quad;
}
