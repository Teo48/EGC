#pragma once
#ifndef __TEMA2_H__
#define __TEMA2_H__
#include <Component/SimpleScene.h>
#include <Core/Engine.h>
#include "Player.h"
#include "Cube.h"
#include "FuelBar.h"

class Tema2 : public SimpleScene {
	public:
		Tema2();
		~Tema2();
		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, int color, int collide);
		void Render2DMesh(Mesh* mesh, Shader* shader, const glm::mat4 &modelMatrix, const glm::vec3 &color);

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;
		Player* player;
		Cube* platform;
		FuelBar* fuelBar;
		glm::vec3 playerCoordinates;
		bool checkCollision(const float xmin, const float ymin, const float zmin,
							const float xmax, const float ymax, const float zmax);
		void RenderCubes();
		void reset();

		bool isCollision;
		int collide;
		int color;
		bool ok;
		bool sw1, sw2;
};

#endif // __TEMA2_H__