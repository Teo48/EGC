#include "LifeGain.h"
#include "vector"
#include "Utils.h"

LifeGain::LifeGain() {
	static auto color = glm::vec3(0.f, 1.f, 0.3f);
	std::vector<VertexFormat> vertices{
		VertexFormat(glm::vec3(0.f, 0.f, 0.f), color), //0
		VertexFormat(glm::vec3(10.f, 20.f, 0.f), color), //1
		VertexFormat(glm::vec3(10.f, -20.f, 0.f), color), //2
		VertexFormat(glm::vec3(5.f, 30.f, 0.f), color), //3
		VertexFormat(glm::vec3(-5.f, 30.f, 0.f), color), //4
		VertexFormat(glm::vec3(-10.f, 20.f, 0.f), color), //5
		VertexFormat(glm::vec3(-10.f, -20.f, 0.f), color), //6
		VertexFormat(glm::vec3(-5.f, -30.f, 0.f), color), //7
		VertexFormat(glm::vec3(5.f, -30.f, 0.f), color) //8
	};

	std::vector<GLushort> indices{
		0, 1, 2,
		0, 3, 4,
		0, 5, 6,
		0, 7, 8
	};

	Utils* u = new Utils();
	lifeGain = u->CreateMesh("lifeGain", vertices, indices);
}

LifeGain::~LifeGain() {
	delete this->lifeGain;
}

Mesh* LifeGain::getLifeGain() {
	return this->lifeGain;
}
