#include "PowerBar.h"
#include "vector"
#include "Utils.h"

PowerBar::PowerBar() {
	static auto color = glm::vec3(0.3f, 0.5f, 0.5f);
	std::vector<VertexFormat> vertices {
		VertexFormat(glm::vec3(0.f, 0.f, 0.f), color),
		VertexFormat(glm::vec3(10.f, 0.f, 0.f), color),
		VertexFormat(glm::vec3(10.f, 2.5f, 0.f), color),
		VertexFormat(glm::vec3(0.f, 2.5f, 0.f), color),
	};

	std::vector<GLushort> indices {
		2, 0, 1,
		0, 2, 3
	};

	Utils* u = new Utils();
	powerBar = u->CreateMesh("powerBar", vertices, indices);
}

PowerBar::~PowerBar() {
	delete this->powerBar;
}

Mesh* PowerBar::getPowerBar() {
	return this->powerBar;
}