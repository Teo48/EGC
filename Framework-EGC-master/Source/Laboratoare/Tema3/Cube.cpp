#pragma once
#include "Cube.h"
#include "iostream"
Cube::Cube() {
	cube = new Mesh("cube");
	cube->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "Box.obj");
}

Cube::~Cube() {
	delete this->cube;
}

void Cube::Init() {
	cubes = std::vector<std::vector<attributes>>(50, std::vector<attributes>(5));
	cubes[0][0].xmin = -4.5f;
	cubes[0][0].xmax = -2.5f;
	cubes[0][0].ymin = -0.05f;
	cubes[0][0].ymax = 0.05f;
	cubes[0][0].zmin = -5.f;
	cubes[0][0].zmax = 1.f;
	cubes[0][0].length = cubes[0][0].zmax - cubes[0][0].zmin;
	cubes[0][0].color = blue;
	cubes[0][0].collide = 0;
	cubes[0][0].hasHolocron = false;

	for (int i = 1; i < 5; ++i) {
		cubes[0][i].xmin = cubes[0][i - 1].xmax;
		cubes[0][i].xmax = cubes[0][i].xmin + 2.f;
		cubes[0][i].ymin = -0.05f;
		cubes[0][i].ymax = 0.05f;
		cubes[0][i].zmin = -5.f;
		cubes[0][i].zmax = 1.f;
		cubes[0][i].length = cubes[0][i].zmax - cubes[0][i].zmin;
		cubes[0][i].color = blue;
		cubes[0][i].collide = 0;
		cubes[0][i].hasHolocron = false;
	}

	for (int j = 1; j < 50; ++j) {
		for (int i = 0; i < 5; ++i) {
			cubes[j][i].xmin = cubes[j - 1][i].xmin;
			cubes[j][i].xmax = cubes[j - 1][i].xmax;
			cubes[j][i].ymin = -0.05f;
			cubes[j][i].ymax = 0.05f;
			cubes[j][i].zmax = cubes[j - 1][i].zmin;
			cubes[j][i].zmin = cubes[j][i].zmax - 5.f;
			cubes[j][i].length = cubes[j][i].zmax - cubes[j][i].zmin;
			cubes[j][i].color = pickColor();
			cubes[j][i].collide = 0;
			cubes[j][i].hasHolocron = false;
		}
	}
	
	for (int i = 0; i < 5; ++i) {
		cubes[1][i].color = blue;
	}
}

int Cube::pickColor() {
	int r = (int)rand() % 105;
	if (r <= 50) {
		return blue;
	}

	if (50 < r && r <= 65) {
		return black;
	}

	if (70 < r && r <= 75) {
		return yellow;
	}

	if (80 < r && r <= 85) {
		return orange;
	}

	if (90 < r && r <= 95) {
		return green;
	}

	if (95 < r && r <= 97) {
		return red;
	}

	if (97 < r && r <= 100) {
		return aqua;
	}

	if (100 < r && r <= 102) {
		return dark_blue;
	}

	return blue;
}
float Cube::randomFloat(float min, float max)
{
	float r = (float)rand() / (float)RAND_MAX;
	return min + r * (max - min);
}

Mesh* Cube::getCube() {
	return this->cube;
}