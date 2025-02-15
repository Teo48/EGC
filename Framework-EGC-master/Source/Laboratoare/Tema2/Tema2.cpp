#include <vector>
#include <iostream>
#include <time.h>
#include <Core/Engine.h>
#include "Transform3.h"
#include "Tema2.h"

Tema2::Tema2()
{

}

Tema2::~Tema2()
{

}


void Tema2::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}


void Tema2::Init()
{
	srand((unsigned int)time(nullptr));
	player = new Player();
	platform = new Cube();
	fuelBar = new FuelBar();
	heart = new Heart();
	camera = new Tema2Camera::Camera();
	camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

	{
		Shader* shader = new Shader("PlayerShader");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/PlayerVertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/PlayerFragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader* shader = new Shader("PlatformShader");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/PlatformVertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/PlatformFragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader* shader = new Shader("FuelBarShader");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FuelBarVertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FuelBarFragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader* shader = new Shader("DeformedPlayerShader");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/DeformedPlayerVertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/DeformedPlayerFragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader* shader = new Shader("HeartShader");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/HeartVertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/HeartFragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	playerCoordinates = glm::vec3(0.f, 0.65f, 0.f);
	isCollision = false;
	collide = 0;
	numLives = 3;
	ok = true;
	sw1 = sw2 = false;
	platform->Init();
	fuelBarCoord = new fuelBarAttr(1.f, -0.985f, 0.875f, -0.99f, 0.87f);
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
	trapSpeedTime = 30.f;
}

void Tema2::RenderCubes() {
	for (int i = 0; i < 50; ++i) {
		for (int j = 0; j < 5; ++j) {
			if (platform->cubes[i][j].color != 6) {
				glm::mat4 modelMatrix = glm::mat4(1);
				modelMatrix *= Transform3D::Translate(platform->cubes[i][j].xmin, 0.f, platform->cubes[i][j].zmax);
				modelMatrix *= Transform3D::Translate(-0.5f, 0.f, -0.5f);
				modelMatrix *= Transform3D::Scale(2.f, 0.1f, -platform->cubes[i][j].length);
				modelMatrix *= Transform3D::Translate(0.5f, 0.f, 0.5f);

				RenderSimpleMesh(platform->getCube(), shaders["PlatformShader"], modelMatrix, platform->cubes[i][j].color, platform->cubes[i][j].collide);
			}
		}
	}
}

void Tema2::Update(float deltaTimeSeconds)
{
	if (firstPerson == true) {
		glm::vec3 pos = glm::vec3(playerCoordinates.x, playerCoordinates.y + 0.65f, playerCoordinates.z - 1.5f);
		camera->Set(glm::vec3(pos), pos + glm::vec3(0.f, 0.f, -1.f), glm::vec3(0, 1, 0));
	}
	else {
		glm::vec3 pos = glm::vec3(playerCoordinates.x, playerCoordinates.y + 2.0f, 5.5f);
		camera->Set(glm::vec3(pos), pos + glm::vec3(0.f, 0.f, -1.f), glm::vec3(0, 1, 0));
	}

	RenderHeart();
	if (!startGame) {
		RenderCubes();
		RenderPlayer("PlayerShader");
		RenderFuelBar();
	}
	else {
		
		if (isRespawned) {
			playerCoordinates.y = 3.f;
			playerCoordinates.x = 0.f;
			isRespawned = false;
			platformSpeed = 10.f;
			fuelBarCoord->fuel = 1.f;
			isDiformed = false;
			respawnAnimation = true;
		}

		if (!isDead) {
			if (isJumpTriggered) {
				(playerCoordinates.y + 0.2f * platformSpeed * deltaTimeSeconds) > 3.f ? playerCoordinates.y = 3.f, isJumpTriggered = false :
					playerCoordinates.y += 0.2f * platformSpeed * deltaTimeSeconds;
			}

			if (playerCoordinates.y == 3.f) {
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

void Tema2::FrameEnd()
{
}

void Tema2::OnInputUpdate(float deltaTime, int mods)
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

void Tema2::OnKeyPress(int key, int mods)
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

void Tema2::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema2::OnWindowResize(int width, int height)
{
}

bool Tema2::checkCollision(const float xmin, const float ymin, const float zmin,
	const float xmax, const float ymax, const float zmax)
{
	return (playerCoordinates.x >= xmin && playerCoordinates.x <= xmax) &&
		((playerCoordinates.y - 0.65f) >= ymin && (playerCoordinates.y - 0.65f) <= ymax) &&
		(playerCoordinates.z >= zmin && playerCoordinates.z <= zmax);

}

void Tema2::reset()
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
}

void Tema2::RenderFuelBar()
{
	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(fuelBarCoord->foreGroundX, fuelBarCoord->foreGroundY, 0.f);
	modelMatrix *= Transform3D::Scale(fuelBarCoord->fuel, 1.f, 1.f);
	Render2DMesh(fuelBar->getforegroundFuelBar(), shaders["FuelBarShader"], modelMatrix, glm::vec3(0.f, 0.82f, 0.3143f));
	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(fuelBarCoord->backGroundX, fuelBarCoord->backGroundY, 0.f);
	Render2DMesh(fuelBar->getbackgroundFuelBar(), shaders["FuelBarShader"], modelMatrix, glm::vec3(1.f, 1.f, 1.f));
}

void Tema2::RenderPlayer(std::string shaderName)
{
	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(playerCoordinates.x, playerCoordinates.y, playerCoordinates.z);
	modelMatrix *= Transform3D::Scale(0.55f, 0.55f, 0.55f);
	RenderSimpleMesh(player->getPlayer(), shaders[shaderName], modelMatrix, animationColor, 0);
}


void Tema2::RenderHeart()
{
	for (int i = numLives; i > 0; --i) {
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(1.f - i * 0.15f, 0.875f, 0.f);
		modelMatrix *= Transform3D::Scale(0.05f, 0.05f, 0.05f);
		Render2DMesh(heart->getHeart(), shaders["HeartShader"], modelMatrix, glm::vec3(1.f, 0.f, 0.f));
	}
}

void Tema2::Render2DMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color)
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

void Tema2::gameOver(std::string goMessage)
{
	std::cout << "========================================================================";
	std::cout << "\n\t\t\t\tGAME OVER!\n";
	std::cout << goMessage;
	std::cout << "========================================================================\n";
	exit(EXIT_SUCCESS);
}

void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, int color, int collide)
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
