#include "Arrow.h"
#include "Utils.h"
#include "vector"

Arrow::Arrow() {
	static auto red = glm::vec3(1.f, 0.f, 0.f);
	static auto black = glm::vec3(0.f, 0.f, 0.f);

	std::vector<VertexFormat> vertices
	{	
		VertexFormat(glm::vec3(0.f, 0.f, 0.f), red),//0
		VertexFormat(glm::vec3(-20.f, 10.f, 0.f), red),//1
		VertexFormat(glm::vec3(-8.f, 0.f, 0.f), red),//2
		VertexFormat(glm::vec3(-20.f, -10.f, 0.f), red),//3
		VertexFormat(glm::vec3(-4.f, 2.f, 0.f), black),//4
		VertexFormat(glm::vec3(-80.f, 2.f, 0.f), black),//5
		VertexFormat(glm::vec3(-80.f, -2.f, 0.f), black),//6
		VertexFormat(glm::vec3(-4.f, -2.f, 0.f), black) //7
	};

	
	std::vector<GLushort> indices{
		0, 1, 2,
		0, 2, 3,
		4, 5, 6,
		4, 6, 7
	};

	Utils *u = new Utils();
	arrow = u->CreateMesh("arrow", vertices, indices);
}

Arrow::~Arrow() {
	delete this->arrow;
}

Mesh* Arrow::getArrow() {
	return this->arrow;
}