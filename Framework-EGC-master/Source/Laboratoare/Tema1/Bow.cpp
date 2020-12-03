#include "Bow.h"
#include "vector"
#include "Utils.h"

Bow::Bow() {
	std::vector<VertexFormat> vertices;
	std::vector<GLushort> indices;
	auto radius = 60.f;
	int j = 0;
	static auto color = glm::vec3(0.f, 0.f, 0.f);
	
	for (auto i = 0.0f; i < glm::pi<GLfloat>(); i += 0.001f, ++j) {
		vertices.emplace_back(VertexFormat(glm::vec3(radius * glm::cos(i), radius * glm::sin(i), 0), color));
		indices.emplace_back(j);
	}
	
	for (auto i = -59.4f; i < 60.f; i += 0.1f, ++j) {
		vertices.emplace_back(VertexFormat(glm::vec3(i, 0.f, 0.f), color));
		indices.emplace_back(++j);
	}

	Utils* u = new Utils();
	glPointSize(3.f);
	bow = u->CreateMesh("bow", vertices, indices);
	bow->SetDrawMode(GL_POINTS);
}

Bow::~Bow() {
	delete this->bow;
}

Mesh* Bow::getBow() {
	return this->bow;
}