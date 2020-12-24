#include "FuelBar.h"
#include "Utils.h"

FuelBar::FuelBar() {
	static auto white = glm::vec3(1.f, 1.f, 1.f);
	std::vector<VertexFormat> backgroundVertices{
		VertexFormat(glm::vec3(0.f, 0.f, 0.f), white),
		VertexFormat(glm::vec3(0.5f, 0.f, 0.f), white),
		VertexFormat(glm::vec3(0.5f, 0.1f, 0.f), white),
		VertexFormat(glm::vec3(0.f, 0.1f, 0.f), white)
	};

	std::vector<GLushort> indices{
		2, 0, 1,
		0, 2, 3
	};

	Utils* u = new Utils();
	backgroundFuelBar = u->CreateMesh("backgroundFuelBar", backgroundVertices, indices);

	static auto green = glm::vec3(0.f, 0.82f, 0.3143f);
	std::vector<VertexFormat> foregroundVertices{
		VertexFormat(glm::vec3(0.f, 0.f, 0.f), green),
		VertexFormat(glm::vec3(0.49f, 0.f, 0.f), green),
		VertexFormat(glm::vec3(0.49f, 0.09f, 0.f), green),
		VertexFormat(glm::vec3(0.f, 0.09f, 0.f), green)
	};

	foregroundFuelBar = u->CreateMesh("foregroundFuelBar", foregroundVertices, indices);
}

FuelBar::~FuelBar() {
	delete this->backgroundFuelBar;
	delete this->foregroundFuelBar;
}

Mesh* FuelBar::getbackgroundFuelBar() {
	return this->backgroundFuelBar;
}

Mesh* FuelBar::getforegroundFuelBar() {
	return this->foregroundFuelBar;
}

