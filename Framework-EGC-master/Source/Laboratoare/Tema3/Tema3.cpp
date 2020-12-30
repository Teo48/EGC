#include <vector>
#include <iostream>
#include <time.h>
#include <Core/Engine.h>
#include "Transform3.h"
#include "Tema3.h"

Tema3::Tema3()
{

}

Tema3::~Tema3()
{

}


void Tema3::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}


void Tema3::Init()
{
	srand((unsigned int)time(nullptr));
	player = new Player();
	platform = new Cube();
	fuelBar = new FuelBar();
	heart = new Heart();
	holocron = new Holocron();
	quad = new Quad();
	camera = new Tema3Camera::Camera();
	camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
	
	LoadTextures();
	LoadShaders();
	
	{
		Mesh* mesh = new Mesh("background");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	
	playerCoordinates = glm::vec3(0.f, 0.65f, 0.f);
	isCollision = false;
	collide = 0;
	numLives = 3;
	ok = true;
	sw1 = sw2 = false;
	platform->Init();
	fuelBarCoord = new fuelBarAttr(1.f, -0.985f, 0.875f, -0.99f, 0.87f);
	scoreBarCoord = new scoreBarAttr(0, 1.25f, 1.15f);
	maxFuel = 1.f;
	platformSpeed = 10.f;
	platformMaxSpeed = 25.f;
	startGame = false;
	isJumpTriggered = false;
	inAir = false;
	isDead = false;
	trapSpeed = false;
	isDiformed = false;
	firstPerson = false;
	isRespawned = false;
	canGetExtraLife = true;
	canLoseLife = true;
	respawnAnimation = false;
	jediBackground = true;
	trapSpeedTime = 30.f;
	score = 0;

	holocron->Init();
	
	for (int k = 0; k < 10;) {
		auto currentLine = rand() % 50;
		for (int j = 0; j < 5; ++j) {
			auto currentCollumn = rand() % 5;
			if (platform->cubes[currentLine][currentCollumn].color == 0 && !platform->cubes[currentLine][currentCollumn].hasHolocron) {
				platform->cubes[currentLine][currentCollumn].hasHolocron = true;
				int position = currentCollumn;
				if (currentLine - 1 < 0) {
					++currentLine;
				}
				float zetmin = platform->cubes[currentLine][currentCollumn].zmin;
				float zetmax = platform->cubes[currentLine][currentCollumn].zmax;
				float xmin = platform->cubes[currentLine][currentCollumn].xmin;
				float xmax = platform->cubes[currentLine][currentCollumn].xmax;
				auto data = holocron->att;
				if (position & 1) {
					data.xmin = xmin + 1.f - 0.517f;
					data.xmax = xmax - 1.f + 0.517;
					data.ymin = 0.5f;
					data.ymax = 1.46f;
					data.zmin = zetmin + 3.f - 0.517f;
					data.zmax = zetmax - 3.f + 0.517f;
					data.type = 1;
					data.collumn = currentCollumn;
					data.line = currentLine;
				}
				else {
					data.xmin = xmin + 1.f - 0.44f;
					data.xmax = xmax - 1.f + 0.44;
					data.ymin = 0.85f;
					data.ymax = 1.85f;
					data.zmin = zetmin + 3.f - 0.44f;
					data.zmax = zetmax - 3.f + 0.44f;
					data.type = 0;
					data.collumn = currentCollumn;
					data.line = currentLine;
				}
				holocron->holocrons.emplace_back(data);
				is_holocron_hit.emplace_back(false);
				++k;
				break;
			}
		}
	}
	
	for (int k = 0; k < 10;) {
		auto currentLine = rand() % 50;
		for (int j = 0; j < 5; ++j) {
			auto currentCollumn = rand() % 5;
			if (platform->cubes[currentLine][currentCollumn].color == 0 && !platform->cubes[currentLine][currentCollumn].hasHolocron) {
				platform->cubes[currentLine][currentCollumn].hasHolocron = true;
				int position = currentCollumn;
				if (currentLine - 1 < 0) {
					++currentLine;
				}
				float zetmin = platform->cubes[currentLine][currentCollumn].zmin;
				float zetmax = platform->cubes[currentLine][currentCollumn].zmax;
				float xmin = platform->cubes[currentLine][currentCollumn].xmin;
				float xmax = platform->cubes[currentLine][currentCollumn].xmax;
				obstacleAttr data;

				data.xmin = xmin + 1.f - 0.75f + 0.25f;
				data.xmax = xmax - 1.f + 0.75f;
				data.ymin = 0.6f;
				data.ymax = 1.25f;
				data.zmin = zetmin + 3.f;
				data.zmax = zetmax - 3.f;
				data.type = position & 1;
				data.collumn = currentCollumn;
				data.line = currentLine;

				obstacles.emplace_back(data);
				is_obstacle_hit.emplace_back(false);
				++k;
				break;
			}
		}
	}

}

void Tema3::RenderCubes() {
	for (int i = 0; i < 50; ++i) {
		for (int j = 0; j < 5; ++j) {
			if (platform->cubes[i][j].color != 6) {
				glm::mat4 modelMatrix = glm::mat4(1);
				modelMatrix *= Transform3D::Translate(platform->cubes[i][j].xmin, 0.f, platform->cubes[i][j].zmax);
				modelMatrix *= Transform3D::Translate(-0.5f, 0.f, -0.5f);
				modelMatrix *= Transform3D::Scale(2.f, 0.1f, -platform->cubes[i][j].length);
				modelMatrix *= Transform3D::Translate(0.5f, 0.f, 0.5f);
				
				RenderMeshTexture(platform->getCube(), shaders["TexturePlatformShader"], modelMatrix, platform->cubes[i][j].color,
					platform->cubes[i][j].collide, mapTextures["floor"], nullptr);
			}
			else {
				glm::mat4 modelMatrix = glm::mat4(1);
				modelMatrix *= Transform3D::Translate(platform->cubes[i][j].xmin, 0.f, platform->cubes[i][j].zmax);
				modelMatrix *= Transform3D::Translate(-0.5f, 0.f, -0.5f);
				modelMatrix *= Transform3D::Scale(2.f, 0.1f, -platform->cubes[i][j].length);
				modelMatrix *= Transform3D::Translate(0.5f, 0.f, 0.5f);
				RenderMeshTexture(platform->getCube(), shaders["TexturePlatformShader"], modelMatrix, platform->cubes[i][j].color,
					platform->cubes[i][j].collide, mapTextures["lava"] , nullptr);
			}
		}
	}
}

void Tema3::Update(float deltaTimeSeconds)
{	
	

	if (firstPerson == true) {
		glm::vec3 pos = glm::vec3(playerCoordinates.x, playerCoordinates.y + 0.65f, playerCoordinates.z - 1.5f);
		camera->Set(glm::vec3(pos), pos + glm::vec3(0.f, 0.f, -1.f), glm::vec3(0, 1, 0));
	}
	else {
		glm::vec3 pos = glm::vec3(playerCoordinates.x, playerCoordinates.y + 2.0f, 8.5f);
		camera->Set(glm::vec3(pos), pos + glm::vec3(0.f, 0.f, -1.f), glm::vec3(0, 1, 0));
	}
	/*
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(0.f, 0.6f, 0.f);
		modelMatrix *= Transform3D::Scale(1.5f, 1.f, 1.f);
		//modelMatrix = glm::scale(modelMatrix, glm::vec3(250.f, 200.f, 200.f));
		modelMatrix *= Transform3D::Translate(-0.5f, -0.5f, 0.f);
		modelMatrix *= Transform3D::Scale(1.f, 2.5f, 1.f);
		modelMatrix *= Transform3D::Translate(0.5f, 0.5f, 0.f);
		RenderMeshTexture(quad->getQuad(), shaders["BackgroundShader"], modelMatrix, -1,
			-1, nullptr, nullptr);
	}
	*/

	for (int i = 0; i < 10; ++i) {
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(obstacles[i].xmin, 0.6f, obstacles[i].zmin);
		modelMatrix *= Transform3D::Scale(1.5f, 1.f, 1.f);
		
		modelMatrix *= Transform3D::Translate(-0.5f, -0.5f, 0.f);
		modelMatrix *= Transform3D::Scale(1.f, 2.5f, 1.f);
		modelMatrix *= Transform3D::Translate(0.5f, 0.5f, 0.f);
		if (obstacles[i].type) {
			RenderMeshTexture(quad->getQuad(), shaders["BackgroundShader"], modelMatrix, -1,
				-1, mapTextures["clone"], nullptr);
		}
		else {
			RenderMeshTexture(quad->getQuad(), shaders["BackgroundShader"], modelMatrix, -1,
				-1, mapTextures["droid"], nullptr);
		}
	}

	RenderBackground();
	RenderScoreBoard();

	for (int i = 0; i < 10; ++i) {
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(holocron->holocrons[i].xmin, holocron->holocrons[i].ymin, holocron->holocrons[i].zmin);

		if (holocron->holocrons[i].type == 0) {
			modelMatrix *= Transform3D::RotateOX(RADIANS(75.f) + (float)(Engine::GetElapsedTime()));
			modelMatrix *= Transform3D::Scale(0.5f, 0.5f, 0.5f);
			RenderMeshTexture(holocron->getJediHolocron(), shaders["HolocronShader"], modelMatrix, 0,
				holocron->holocrons[i].collide, mapTextures["jediHolocron"], nullptr);
		}
		else {
			modelMatrix *= Transform3D::RotateOY(RADIANS(75.f) + (float)(Engine::GetElapsedTime()));
			modelMatrix *= Transform3D::Scale(0.01f, 0.01f, 0.01f);
			RenderMeshTexture(holocron->getSithHolocron(), shaders["HolocronShader"], modelMatrix, 1,
				holocron->holocrons[i].collide, mapTextures["sithHolocron"], nullptr);
		}
	}

	RenderHeart();
	if (!startGame) {
		RenderCubes();
		RenderPlayer("PlayerShader");
		RenderFuelBar();
	}
	else {
		
		if (isRespawned) {
			playerCoordinates.y = 4.f;
			playerCoordinates.x = 0.f;
			isRespawned = false;
			platformSpeed = 10.f;
			fuelBarCoord->fuel = 1.f;
			isDiformed = false;
			respawnAnimation = true;
		}

		if (!isDead) {
			if (isJumpTriggered) {
				(playerCoordinates.y + 0.2f * platformSpeed * deltaTimeSeconds) > 4.f ? playerCoordinates.y = 4.f, isJumpTriggered = false :
					playerCoordinates.y += 0.2f * platformSpeed * deltaTimeSeconds;
			}

			if (playerCoordinates.y == 4.f) {
				inAir = true;
			}

			if (inAir) {
				(playerCoordinates.y - 0.2f * platformSpeed * deltaTimeSeconds) < 0.65f ? playerCoordinates.y = 0.65f, inAir = false :
					playerCoordinates.y -= 0.2f * platformSpeed * deltaTimeSeconds;
			}

			if (playerCoordinates.y == 0.65f) {
				respawnAnimation = false;
				animationColor = 0;
			}

			if (trapSpeed) {
				platformSpeed = 30.f;
				(trapSpeedTime - 10.f * deltaTimeSeconds) < 0.f ? trapSpeed = false, isDiformed = false, platformSpeed = oldPlatformSpeed, trapSpeedTime = 30.f :
					trapSpeedTime -= 10.f * deltaTimeSeconds;
			}

			if (!isDiformed && !respawnAnimation) {
				RenderPlayer("PlayerShader");
			}
			else if (isDiformed && !respawnAnimation) {
				RenderPlayer("DeformedPlayerShader");
			}
			else if (respawnAnimation) {
				animationColor = 1;
				RenderPlayer("DeformedPlayerShader");
			}

			for (int i = 0; i < 50; ++i) {
				for (int j = 0; j < 5; ++j) {
					platform->cubes[i][j].zmax += platformSpeed * deltaTimeSeconds;
					platform->cubes[i][j].zmin += platformSpeed * deltaTimeSeconds;
				}
			}

			// Update holocrons' coordinates
			
			for (int i = 0; i < 10; ++i) {
				auto &it = holocron->holocrons[i];
				it.zmax += platformSpeed * deltaTimeSeconds;
				it.zmin += platformSpeed * deltaTimeSeconds;
				obstacles[i].zmax += platformSpeed * deltaTimeSeconds;
				obstacles[i].zmin += platformSpeed * deltaTimeSeconds;
			}
		
			reset();

			for (int i = 0; i < 50; ++i) {
				for (int j = 0; j < 5; ++j) {
					if (checkCollision(platform->cubes[i][j].xmin - 0.5f, platform->cubes[i][j].ymin, platform->cubes[i][j].zmax - platform->cubes[i][j].length - 0.5f,
						platform->cubes[i][j].xmin + 1.5f, platform->cubes[i][j].ymax, platform->cubes[i][j].zmax - 0.5f)) {
						platform->cubes[i][j].collide = 1;

						// If the player hits a green platform, he gets fuel
						if (platform->cubes[i][j].color == 5) {
							fuelBarCoord->fuel + 0.01f > 1.f ? fuelBarCoord->fuel = maxFuel : fuelBarCoord->fuel += 0.01f;
						}

						// If the player hits an yellow platform, he loses fuel
						if (platform->cubes[i][j].color == 3) {
							fuelBarCoord->fuel - 0.01f < 0.f ? isDead = true : fuelBarCoord->fuel -= 0.01f;
						}

						// If the player hits a red platform, the game is over

						if (platform->cubes[i][j].color == 2) {
							gameOver("");
						}

						// If the player hits an aqua platform, he gets an extralife
						
						if (platform->cubes[i][j].color == 7 && canGetExtraLife) {
							++numLives;
							numLives = std::min(numLives, 5);
							canGetExtraLife = false;
						}
						else if (platform->cubes[i][j].color != 7) {
							canGetExtraLife = true;
						}

						// If the player hits a dark blue platform, he loses a life

						if (platform->cubes[i][j].color == 1 && canLoseLife) {
							--numLives;
							canLoseLife = false;
							if (numLives == 0) {
								gameOver("");
								exit(EXIT_SUCCESS);
							}
						}
						else if (platform->cubes[i][j].color != 1) {
							canLoseLife = true;
						}

						// If the player this an orange platform, he's stuck at max speed

						if (platform->cubes[i][j].color == 4 && !trapSpeed) {
							trapSpeed = true;
							isDiformed = true;
							oldPlatformSpeed = platformSpeed;
						}
					}
					else {
						platform->cubes[i][j].collide = 0;
					}

					if (checkCollision(platform->cubes[i][j].xmin, platform->cubes[i][j].ymin, platform->cubes[i][j].zmax - platform->cubes[i][j].length - 0.5f,
						platform->cubes[i][j].xmin + 1.f, platform->cubes[i][j].ymax, platform->cubes[i][j].zmax - 1.15f) && platform->cubes[i][j].color == 6) {
						platform->cubes[i][j].collide = 0;
						isDead = true;
					}
				}
			}

			for (int i = 0; i < 10; ++i) {
				const auto& it = holocron->holocrons[i];
				if (holocronCollisison(it.xmin - 0.5f, it.ymin, it.zmin, it.xmax - 0.5f, it.ymax, it.zmax) && is_holocron_hit[i] == false) {
					is_holocron_hit[i] = true;
					holocron->holocrons[i].collide = 1;
					if (it.type == 0) {
						jediBackground = true;
						scoreBarCoord->score += 0.01f;
					}
					else {
						jediBackground = false;
						scoreBarCoord->score += 0.02f;
					}
					break;
				}
				const auto& oit = obstacles[i];
				if (holocronCollisison(oit.xmin - 0.25f, oit.ymin, oit.zmin, oit.xmax - 0.5f, oit.ymax, oit.zmax) && is_obstacle_hit[i] == false) {
					is_obstacle_hit[i] = true;
					isDead = true;
				}
			}

			// If the players gets outside the playing field, he dies
			if ((playerCoordinates.y == 0.65f && playerCoordinates.x < -5.5f) || (playerCoordinates.y == 0.65f && playerCoordinates.x > 5.5f)) {
				isDead = true;
			}

			RenderCubes();
			{
				fuelBarCoord->fuel -= 0.002f * platformSpeed * deltaTimeSeconds;
				if (fuelBarCoord->fuel < 0.f) {
					isDead = true;
				}
				RenderFuelBar();
			}
		}
		else {
			if (playerCoordinates.y > -10.f) {
				playerCoordinates.y -= 2.f * deltaTimeSeconds;
			}
			RenderPlayer("PlayerShader");
			RenderCubes();
			RenderFuelBar();
			if (playerCoordinates.y < -10.f) {
				--numLives;
				isDead = false;
				isRespawned = true;
			}

			if (numLives == 0) {
				gameOver("");
				exit(EXIT_SUCCESS);
			}
		}
	}
}

void Tema3::FrameEnd()
{
}

void Tema3::OnInputUpdate(float deltaTime, int mods)
{
	if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT) && !isDead) {

		if (!trapSpeed) {
			if (window->KeyHold(GLFW_KEY_W)) {
				platformSpeed > 25.f ? platformSpeed = platformMaxSpeed : platformSpeed += 10.f * deltaTime;
			}

			if (window->KeyHold(GLFW_KEY_S)) {
				platformSpeed < 3.f ? platformSpeed = 3.f : platformSpeed -= 10.f * deltaTime;
			}
		}

		if (window->KeyHold(GLFW_KEY_A)) {
			playerCoordinates.x -= 5.f * deltaTime;
		}

		if (window->KeyHold(GLFW_KEY_D)) {
			playerCoordinates.x += 5.f * deltaTime;
		}
	}

}

void Tema3::OnKeyPress(int key, int mods)
{
	if (!isJumpTriggered && !inAir) {
		if (key == GLFW_KEY_SPACE) {
			isJumpTriggered = true;
		}
	}

	if (key == GLFW_KEY_ENTER) {
		startGame = true;
	}

	if (key == GLFW_KEY_C) {
		firstPerson = !firstPerson;
	}
}

void Tema3::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Tema3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema3::OnWindowResize(int width, int height)
{
}

bool Tema3::checkCollision(const float xmin, const float ymin, const float zmin,
	const float xmax, const float ymax, const float zmax)
{
	return (playerCoordinates.x >= xmin && playerCoordinates.x <= xmax) &&
		((playerCoordinates.y - 0.65f) >= ymin && (playerCoordinates.y - 0.65f) <= ymax) &&
		(playerCoordinates.z >= zmin && playerCoordinates.z <= zmax);

}

bool Tema3::holocronCollisison(const float xmin, const float ymin, const float zmin, const float xmax, const float ymax, const float zmax)
{
	auto x = std::max(xmin, std::min(playerCoordinates.x, xmax));
	auto y = std::max(ymin, std::min(playerCoordinates.y, ymax));
	auto z = std::max(zmin, std::min(playerCoordinates.z, zmax));

	auto distance = sqrt((x - playerCoordinates.x) * (x - playerCoordinates.x) +
		(y - playerCoordinates.y) * (y - playerCoordinates.y) +
		(z - playerCoordinates.z) * (z - playerCoordinates.z));

	return distance < 0.65f;
}

void Tema3::reset()
{
	if (platform->cubes[21][0].zmax > 10.f && sw1 == false) {

		for (int i = 0; i < 5; ++i) {
			platform->cubes[0][i].zmax = platform->cubes[49][i].zmin;
			platform->cubes[0][i].zmin = platform->cubes[0][i].zmax - platform->cubes[0][i].length;
		}

		for (int i = 1; i <= 21; ++i) {
			for (int j = 0; j < 5; ++j) {
				platform->cubes[i][j].zmax = platform->cubes[i - 1][j].zmin;
				platform->cubes[i][j].zmin = platform->cubes[i][j].zmax - platform->cubes[i][j].length;
			}
		}

		sw1 = true;
	}

	if (platform->cubes[49][0].zmax > 10.f && sw1 == true) {
		for (int i = 21; i <= 49; ++i) {
			for (int j = 0; j < 5; ++j) {
				platform->cubes[i][j].zmax = platform->cubes[i - 1][j].zmin;
				platform->cubes[i][j].zmin = platform->cubes[i][j].zmax - platform->cubes[i][j].length;
			}
		}
		sw1 = false;
	}

	for (int i = 0; i < 10; ++i) {
		auto& it = holocron->holocrons[i];
		if (it.zmax > 15.f) {
			is_holocron_hit[i] = false;
			holocron->holocrons[i].collide = 0;
			if (it.type == 1) {
				it.zmax = platform->cubes[it.line][it.collumn].zmax - 3.f + 0.517f;
				it.zmin = platform->cubes[it.line][it.collumn].zmin + 3.f - 0.517f;
			}
			else {
				it.zmax = platform->cubes[it.line][it.collumn].zmax - 3.f + 0.44f;
				it.zmin = platform->cubes[it.line][it.collumn].zmin + 3.f - 0.44f;
			}
		}
		auto& oit = obstacles[i];

		if (oit.zmax > 15.f) {
			is_obstacle_hit[i] = false;
			obstacles[i].zmax = platform->cubes[oit.line][oit.collumn].zmax - 3.f;
			obstacles[i].zmin = platform->cubes[oit.line][oit.collumn].zmin + 3.f;
		}
	}
}

int Tema3::getColumn(const int x)
{
	if (x >= -4.5 && x <= -2.5) {
		return -2;
	}

	if (x >= -2.5 && x <= -0.5) {
		return -1;
	}

	if (x >= -0.5 && x <= 1.5) {
		return 0;
	}

	if (x >= 1.5 && x <= 3.5) {
		return 1;
	}

	return 2;
}

void Tema3::RenderFuelBar()
{
	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(fuelBarCoord->foreGroundX, fuelBarCoord->foreGroundY, 0.f);
	modelMatrix *= Transform3D::Scale(fuelBarCoord->fuel, 1.f, 1.f);
	Render2DMesh(fuelBar->getforegroundFuelBar(), shaders["FuelBarShader"], modelMatrix, glm::vec3(0.f, 0.82f, 0.3143f));
	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(fuelBarCoord->backGroundX, fuelBarCoord->backGroundY, 0.f);
	Render2DMesh(fuelBar->getbackgroundFuelBar(), shaders["FuelBarShader"], modelMatrix, glm::vec3(1.f, 1.f, 1.f));
}

void Tema3::RenderPlayer(std::string shaderName)
{
	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(playerCoordinates.x, playerCoordinates.y, playerCoordinates.z);
	modelMatrix *= Transform3D::Scale(0.55f, 0.55f, 0.55f);
	RenderSimpleMesh(player->getPlayer(), shaders[shaderName], modelMatrix, animationColor, 0);
}


void Tema3::RenderHeart()
{
	for (int i = numLives; i > 0; --i) {
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(1.f - i * 0.15f, 0.875f, 0.f);
		modelMatrix *= Transform3D::Scale(0.05f, 0.05f, 0.05f);
		Render2DMesh(heart->getHeart(), shaders["HeartShader"], modelMatrix, glm::vec3(1.f, 0.f, 0.f));
	}
}

void Tema3::RenderBackground()
{
	if (jediBackground) {
		
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::scale(modelMatrix, glm::vec3(250.f, 200.f, 200.f));
		RenderMeshTexture(meshes["background"], shaders["BackgroundShader"], modelMatrix, -1,
			-1, mapTextures["jediBackground"], nullptr);
		
	}
	else {
		
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::scale(modelMatrix, glm::vec3(250.f, 200.f, 200.f));
		RenderMeshTexture(meshes["background"], shaders["BackgroundShader"], modelMatrix, -1,
			-1, mapTextures["sithBackground"], nullptr);
		
	}
}

void Tema3::RenderScoreBoard()
{
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(0.87f, 0.75f, 0.f);
		modelMatrix *= Transform3D::Scale(0.25f, 0.25f, 1.f);
		modelMatrix = glm::rotate(modelMatrix, RADIANS(90), glm::vec3(0, 0, 1));
		RenderMesh2DTexture(quad->getQuad(), shaders["QuadShader"], modelMatrix, mapTextures["windu"]);
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);

		modelMatrix *= Transform3D::Translate(scoreBarCoord->x, scoreBarCoord->y, 0.f);
		modelMatrix *= Transform3D::Translate(-0.5f, -0.5f, 0.f);
		modelMatrix *= Transform3D::Scale(-scoreBarCoord->score, 0.2f, 1.f);
		modelMatrix *= Transform3D::Translate(0.5f, 0.5f, 0.f);
		modelMatrix = glm::rotate(modelMatrix, RADIANS(270), glm::vec3(0, 0, 1));
		RenderMesh2DTexture(quad->getQuad(), shaders["QuadShader"], modelMatrix, mapTextures["purple"]);
	}
}

void Tema3::LoadShaders()
{
	{
		Shader* shader = new Shader("PlayerShader");
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/PlayerVertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/PlayerFragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader* shader = new Shader("PlatformShader");
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/PlatformVertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/PlatformFragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader* shader = new Shader("FuelBarShader");
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/FuelBarVertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/FuelBarFragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader* shader = new Shader("DeformedPlayerShader");
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/DeformedPlayerVertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/DeformedPlayerFragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader* shader = new Shader("HeartShader");
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/HeartVertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/HeartFragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader* shader = new Shader("TexturePlatformShader");
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/TexturePlatformVertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/TexturePlatformFragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader* shader = new Shader("HolocronShader");
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/HolocronVertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/HolocronFragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader* shader = new Shader("BackgroundShader");
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/BackgroundVertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/BackgroundFragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader* shader = new Shader("QuadShader");
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/QuadVertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/QuadFragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
}

void Tema3::LoadTextures()
{
	const std::string textureLoc = "Source/Laboratoare/Tema3/Textures/";

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "lava.jpg").c_str(), GL_REPEAT);
		mapTextures["lava"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "floor.png").c_str(), GL_REPEAT);
		mapTextures["floor"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "red.jpg").c_str(), GL_REPEAT);
		mapTextures["sithHolocron"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "blueholocron.jpg").c_str(), GL_REPEAT);
		mapTextures["jediHolocron"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "blue.jpg").c_str(), GL_REPEAT);
		mapTextures["jediBackground"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "redbackground.jpg").c_str(), GL_REPEAT);
		mapTextures["sithBackground"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "windu.png").c_str(), GL_REPEAT);
		mapTextures["windu"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "purple.png").c_str(), GL_REPEAT);
		mapTextures["purple"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "clone.png").c_str(), GL_REPEAT);
		mapTextures["clone"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "spaceship.png").c_str(), GL_REPEAT);
		mapTextures["spaceship"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "droid.png").c_str(), GL_REPEAT);
		mapTextures["droid"] = texture;
	}
}

void Tema3::Render2DMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	auto modelLocation = glGetUniformLocation(shader->program, "Model");

	// TODO : set shader uniform "Model" to modelMatrix
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));


	auto colorLocation = glGetUniformLocation(shader->GetProgramID(), "Color");
	glUniform3fv(colorLocation, 1, glm::value_ptr(color));

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

void Tema3::RenderMeshTexture(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, int color, int collide, Texture2D* texture1, Texture2D* texture2)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// TODO : get shader location for uniform mat4 "Model"
	auto modelLocation = glGetUniformLocation(shader->program, "Model");

	// TODO : set shader uniform "Model" to modelMatrix
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// TODO : get shader location for uniform mat4 "View"
	auto viewLocation = glGetUniformLocation(shader->GetProgramID(), "View");

	// TODO : set shader uniform "View" to viewMatrix
	glm::mat4 viewMatrix = camera->GetViewMatrix();
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// TODO : get shader location for uniform mat4 "Projection"
	auto projectionLocation = glGetUniformLocation(shader->GetProgramID(), "Projection");

	// TODO : set shader uniform "Projection" to projectionMatrix

	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	auto clockLocation = glGetUniformLocation(shader->GetProgramID(), "Clock");
	auto time = Engine::GetElapsedTime();
	glUniform1f(clockLocation, time);

	auto collideLocation = glGetUniformLocation(shader->GetProgramID(), "Collide");
	glUniform1i(collideLocation, collide);

	auto colorLocation = glGetUniformLocation(shader->GetProgramID(), "Color");
	glUniform1i(colorLocation, color);

	if (texture1)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());
		glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);
	}

	if (texture2)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2->GetTextureID());
		glUniform1i(glGetUniformLocation(shader->program, "texture_2"), 1);
	}

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);

}

void Tema3::RenderMesh2DTexture(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture1)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// TODO : get shader location for uniform mat4 "Model"
	auto modelLocation = glGetUniformLocation(shader->program, "Model");

	// TODO : set shader uniform "Model" to modelMatrix
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));


	if (texture1)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());
		glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);
	}

	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);

}

void Tema3::gameOver(std::string goMessage)
{
	std::cout << "========================================================================";
	std::cout << "\n\t\t\t\tGAME OVER!\n";
	std::cout << goMessage;
	std::cout << "========================================================================\n";
	exit(EXIT_SUCCESS);
}

void Tema3::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, int color, int collide)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// TODO : get shader location for uniform mat4 "Model"
	auto modelLocation = glGetUniformLocation(shader->program, "Model");

	// TODO : set shader uniform "Model" to modelMatrix
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// TODO : get shader location for uniform mat4 "View"
	auto viewLocation = glGetUniformLocation(shader->GetProgramID(), "View");

	// TODO : set shader uniform "View" to viewMatrix
	glm::mat4 viewMatrix = camera->GetViewMatrix();
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// TODO : get shader location for uniform mat4 "Projection"
	auto projectionLocation = glGetUniformLocation(shader->GetProgramID(), "Projection");

	// TODO : set shader uniform "Projection" to projectionMatrix

	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	auto clockLocation = glGetUniformLocation(shader->GetProgramID(), "Clock");
	auto time = Engine::GetElapsedTime();
	glUniform1f(clockLocation, time);

	auto collideLocation = glGetUniformLocation(shader->GetProgramID(), "Collide");
	glUniform1i(collideLocation, collide);

	auto colorLocation = glGetUniformLocation(shader->GetProgramID(), "Color");
	glUniform1i(colorLocation, color);

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}
