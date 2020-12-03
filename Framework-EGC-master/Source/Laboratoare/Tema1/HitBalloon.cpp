#include "HitBalloon.h"
#include "vector"
#include "Utils.h"

HitBalloon::HitBalloon(glm::vec3 &color) {
	std::vector<VertexFormat> vertices{
		VertexFormat(glm::vec3(25.f, -59.f, 0.f), color), // 0
		VertexFormat(glm::vec3(55.f, -29.f, 0.f), color), // 1
		VertexFormat(glm::vec3(-30.f, -10.f, 0.f), color), // 2
		VertexFormat(glm::vec3(-75.f, -59.f, 0.f), color), // 3
	};
	
	std::vector<GLushort> indices{
		0, 1, 2,
		1, 3, 0
	};

	Utils* u = new Utils();
	hitBalloon = u->CreateMesh("HitBalon", vertices, indices);

	std::vector<VertexFormat> verticesTriangle{
		VertexFormat(glm::vec3(0.f, -59.f, 0.f), color),
		VertexFormat(glm::vec3(-5.f, -70.f, 0.f), color),
		VertexFormat(glm::vec3(5.f, -70.f, 0.f), color)
	};

	std::vector<GLushort> indicesTriangle{
		0, 1, 2
	};

	hitBalloonTriangle = u->CreateMesh("hitBalonTriangle", verticesTriangle, indicesTriangle);

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
	hitBalloonLine = u->CreateMesh("hitBalonLine", verticesLine, indicesLine);
	hitBalloonLine->SetDrawMode(GL_LINE_STRIP);
}

HitBalloon::~HitBalloon() {
	delete this->hitBalloon;
	delete this->hitBalloonLine;
	delete this->hitBalloonTriangle;
}

Mesh* HitBalloon::getHitBalloon() {
	return this->hitBalloon;
}

Mesh* HitBalloon::getHitBalloonTriangle() {
	return this->hitBalloonTriangle;
}


Mesh* HitBalloon::getHitBalloonLine() {
	return this->hitBalloonLine;
}