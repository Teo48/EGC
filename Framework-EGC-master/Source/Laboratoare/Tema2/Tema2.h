#pragma once
#ifndef __TEMA2_H__
#define __TEMA2_H__
#include <Component/SimpleScene.h>
#include <Core/Engine.h>
#include "Player.h"
#include "Cube.h"
#include "FuelBar.h"
#include "LabCamera.h"

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
		glm::mat4 projectionMatrix;
		bool checkCollision(const float xmin, const float ymin, const float zmin,
							const float xmax, const float ymax, const float zmax);
		void RenderCubes();
		void RenderFuelBar();
		void RenderPlayer(const std::string shaderName);
		void reset();
		Tema2Camera::Camera* camera;
		bool isCollision;
		int collide;
		int color;
		bool ok;
		bool sw1, sw2;
		bool startGame;
		bool isDead;
		float maxFuel;
		float platformSpeed;
		float platformMaxSpeed;
		float trapSpeedTime;
		float oldPlatformSpeed;
		bool isJumpTriggered;
		bool inAir;
		bool trapSpeed;
		bool isDiformed;
		bool firstPerson;

		typedef struct fuelBarAttr {
			float fuel;
			float foreGroundX;
			float foreGroundY;
			float backGroundX;
			float backGroundY;
			
			fuelBarAttr() {}

			fuelBarAttr(const float fuel, const float foreGroundX,
						const float foreGroundY, const float backGroundX,
						const float backGroundY) {
				this->fuel = fuel;
				this->foreGroundX = foreGroundX;
				this->foreGroundY = foreGroundY;
				this->backGroundX = backGroundX;
				this->backGroundY = backGroundY;
			}
		} fuelBarAttr;

		fuelBarAttr* fuelBarCoord;

		void gameOver(const std::string goMessage);
};

#endif // __TEMA2_H__