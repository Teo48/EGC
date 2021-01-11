#include "Temple.h"

Temple::Temple()
{
	std::vector<glm::vec3> vertices
	{
		// Trunk lower base
		glm::vec3(0.f, 0.f, 0.f), // Bottom left
		glm::vec3(4.f,  0.f, 0.f),
		glm::vec3(4.f,  0.f, -2.f),
		glm::vec3(0.f, 0.f, -2.f),

		// Trunk upper base
		glm::vec3(1.f, 2.f, 0.f),
		glm::vec3(3.f,  2.f, 0.f),
		glm::vec3(3.f,  2.f, -1.5f),
		glm::vec3(1.f, 2.f, -1.5f),

		// Mid trunk lower base
		glm::vec3(1.2f, 2.5f, -0.2f),
		glm::vec3(2.8f, 2.5f, -0.2f),
		glm::vec3(2.8f, 2.5f, -1.3f),
		glm::vec3(1.2f, 2.5f, -1.3f),

		// Mid trunk upper base
		glm::vec3(1.6f, 3.5f, -0.4f),
		glm::vec3(2.4f, 3.5f, -0.4f),
		glm::vec3(2.4f, 3.5f, -1.2f),
		glm::vec3(1.6f, 3.5f, -1.2f),

		// Pyramald
		glm::vec3(1.75f, 4.f, -0.6f),
		glm::vec3(2.25f, 4.f, -0.6f),
		glm::vec3(2.25f, 4.f, -1.f),
		glm::vec3(1.75f, 4.f, -1.f),
		glm::vec3(2.f, 4.65f, -0.8f)

	};

	std::vector<glm::vec3> normals
	{
		glm::vec3(0, 1, 1),
		glm::vec3(1, 0, 1),
		glm::vec3(1, 0, 0),
		glm::vec3(0, 1, 0)
	};

	std::vector<glm::vec2> textureCoords{
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.25f, 0.4301075268817204f),
		glm::vec2(0.75f, 0.4301075268817204f),
		glm::vec2(0.3f, 0.5376344086021505f),
		glm::vec2(0.7f, 0.5376344086021505f),
		glm::vec2(0.4f, 0.7526881720430108f),
		glm::vec2(0.6f, 0.7526881720430108f),
		glm::vec2(0.4375f, 0.8602150537634408f),
		glm::vec2(0.5625f, 0.8602150537634408f),
		glm::vec2(0.5f, 1.0f)
	};
	
	std::vector<unsigned short> indices =
	{
		0, 1, 4,
		1, 5, 4,
		0, 1, 3,
		1, 2, 3,
		2, 6, 5,
		1, 2, 5,
		3, 2, 7,
		3, 6, 7,
		0, 3, 4,
		3, 7, 4,
		4, 5, 7,
		5, 6, 7,

		8, 9, 11,
		9, 10, 11,
		8, 9, 12,
		9, 13, 12,
		9, 10, 13,
		10, 14, 13,
		8, 12, 11,
		11, 12, 15,
		11, 10, 15,
		10, 14, 15,
		12, 13, 15,
		13, 14, 15,

		16, 17, 19,
		17, 18, 19,
		16, 17, 20,
		17, 18, 20,
		18, 20, 19,
		16, 20, 19,
	};

	temple = new Mesh("temple");
	temple->InitFromData(vertices, normals, textureCoords, indices);
}

Temple::~Temple()
{
	delete this->temple;
}

Mesh* Temple::getTemple()
{
	return this->temple;
}
