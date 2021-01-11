#pragma once
#ifndef __TEMA3_H__
#define __TEMA3_H__
#include <Component/SimpleScene.h>
#include <Core/Engine.h>
#include "Player.h"
#include "Cube.h"
#include "FuelBar.h"
#include "LabCamera.h"
#include "Heart.h"
#include "Holocron.h"
#include "Quad.h"
#include "Temple.h"
#include "Planet.h"

class Tema3 : public SimpleScene {
	public:
		Tema3();
		~Tema3();
		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, int color, int collide);
		void Render2DMesh(Mesh* mesh, Shader* shader, const glm::mat4 &modelMatrix, const glm::vec3 &color);
		void RenderMeshTexture(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, int color, int collide, Texture2D* texture1, Texture2D* texture2);
		void RenderMesh2DTexture(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture1);
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
		Heart* heart;
		Holocron* holocron;
		Quad* quad;
		Temple* temple;
		Planet* planet;
		glm::vec3 playerCoordinates;
		glm::mat4 projectionMatrix;
		bool checkCollision(const float xmin, const float ymin, const float zmin,
							const float xmax, const float ymax, const float zmax);
		bool holocronCollisison(const float xmin, const float ymin, const float zmin,
								const float xmax, const float ymax, const float zmax);
		void RenderCubes();
		void RenderFuelBar();
		void RenderPlayer(const std::string shaderName);
		void RenderHeart();
		void RenderBackground();
		void RenderScoreBoard();
		void RenderHolocrons();
		void RenderObstacles();
		void LoadShaders();
		void LoadTextures();
		void InitHolocrons();
		void InitObstacles();
		void reset();
		int getColumn(const int x);
		Tema3Camera::Camera* camera;
		bool isCollision;
		int collide;
		int color;
		int animationColor;
		int numLives;
		int score;
		bool ok;
		bool sw1, sw2;
		bool startGame;
		bool isDead;
		bool isRespawned;
		bool canGetExtraLife;
		bool canLoseLife;
		bool respawnAnimation;
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
		bool hitGreen;
		int jediBackground;
	
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

		typedef struct scoreBarAttr {
			float score;
			float x;
			float y;

			scoreBarAttr() {}

			scoreBarAttr(const float score, const float x, const float y) {
				this->score = score;
				this->x = x;
				this->y = y;
			}
		} scoreBarAttr;

		typedef struct obstacleAttr {
			float xmin;
			float xmax;
			float ymin;
			float ymax;
			float zmin;
			float zmax;
			int type;
			int collide;
			int collumn;
			int line;
		} obstacleAttr;

		typedef struct decorativeAttr {
			float x;
			float y;
			float z;
		} decorativeAttr;

		std::vector<obstacleAttr> obstacles;
		std::vector<decorativeAttr> sithDecorative;
		std::vector<decorativeAttr> jediDecorative;
		scoreBarAttr* scoreBarCoord;

		std::unordered_map<std::string, Texture2D*> mapTextures;
		std::vector<bool> is_holocron_hit;
		std::vector<bool> is_obstacle_hit;
		void gameOver(const std::string goMessage);
};

#endif // __TEMA3_H__