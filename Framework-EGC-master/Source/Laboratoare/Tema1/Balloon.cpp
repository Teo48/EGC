#include "Balloon.h"
#include "vector"
#include "Utils.h"

Balloon::Balloon(glm::vec3 &color) {
	std::vector<VertexFormat> vertices;
	std::vector<GLushort> indices;
	auto radius = 60.f;
	int j = 0;
	for (auto i = 0.f; i < 2 * glm::pi<GLfloat>(); i += 0.001f, ++j) {
		vertices.emplace_back(glm::vec3(radius * glm::cos(i), radius * glm::sin(i), 0), color);
		indices.emplace_back(j);
	}

	Utils* u = new Utils();
	balloon= u->CreateMesh("ballon", vertices, indices);
	balloon->SetDrawMode(GL_TRIANGLE_FAN);
	
	std::vector<VertexFormat> verticesTriangle {
		VertexFormat(glm::vec3(0.f, -59.f, 0.f), color),
		VertexFormat(glm::vec3(-5.f, -70.f, 0.f), color),
		VertexFormat(glm::vec3(5.f, -70.f, 0.f), color)
	};
	
	std::vector<GLushort> indicesTriangle {
		0, 1, 2
	};

	balloonTriangle = u->CreateMesh("ballonTriangle", verticesTriangle, indicesTriangle);

	static auto black = glm::vec3(0.f, 0.f, 0.f);
	std::vector<VertexFormat> verticesLine{
		VertexFormat(glm::vec3(0.f, -70.f, 0.f), black),
		VertexFormat(glm::vec3(10.f, -80.f, 0.f), black),
		VertexFormat(glm::vec3(0.f, -100.f, 0.f), black),
		VertexFormat(glm::vec3(15.f, -120.f, 0.f), black),
	};

	std::vector<GLushort> indicesLine{
		0, 1, 2, 3
	};

	glLineWidth(5.0f);
	balloonLine = u->CreateMesh("ballonLine", verticesLine, indicesLine);
	balloonLine->SetDrawMode(GL_LINE_STRIP);
}

Balloon::~Balloon() {
	delete this->balloon;
	delete this->balloonLine;
	delete this->balloonTriangle;
}

Mesh* Balloon::getBalloon() {
	return this->balloon;
}

Mesh* Balloon::getBalloonTriangle() {
	return this->balloonTriangle;
}


Mesh* Balloon::getBalloonLine() {
	return this->balloonLine;
}
