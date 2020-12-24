#include "Heart.h"
#include "Utils.h"
#include "vector"
#include <iostream>

// Credits: https://gist.github.com/tuanpt216/6e01873e50528c17a35e
Heart::Heart() {
	static auto red = glm::vec3(1.f, 0.f, 0.f);
	std::vector<VertexFormat> vertices;
	std::vector<GLushort> indices;
	int j = 0;

	for (float i = -1.139f; i <= 1.139f; i += 0.001f, j += 1) {
		float delta = cbrt(i * i) * cbrt(i * i) - 4 * i * i + 4;
		float y1 = (cbrt(i * i) + sqrt(delta)) / 2;
		vertices.emplace_back(glm::vec3(i, y1, 0), red);
		indices.emplace_back(j);
	}

	for (float i = -1.139f; i <= 1.139f; i += 0.001f, j += 1) {
		float delta = cbrt(i * i) * cbrt(i * i) - 4 * i * i + 4;
		float y2 = (cbrt(i * i) - sqrt(delta)) / 2;
		vertices.emplace_back(glm::vec3(i, y2, 0), red);
		indices.emplace_back(j + 1);
	}

	Utils* u = new Utils();
	heart = u->CreateMesh("heart", vertices, indices);
	heart->SetDrawMode(GL_TRIANGLE_FAN);
}

Heart::~Heart() {
	delete this->heart;
}

Mesh* Heart::getHeart() {
	return this->heart;
}