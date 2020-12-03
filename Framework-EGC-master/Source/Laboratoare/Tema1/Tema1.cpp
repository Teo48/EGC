#include "Tema1.h"

#include <vector>
#include <iostream>
#include <time.h>
#include <Core/Engine.h>
#include "Transform.h"

using namespace std;

Tema1::Tema1()
{
}

Tema1::~Tema1()
{

}

void Tema1::Init()
{
	srand((unsigned int)time(nullptr));
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);
	livesLeft = 3;
	numShurikens = 3;
	angularStep = 1;
	powerScale = 1;
	arrowSpeed = 15.f;
	isReleased = false;
	lifeGainActive = false;
	bow = new Bow();
	arrow = new Arrow();
	shuriken = new Shuriken();
	powerBar = new PowerBar();
	heart = new Heart();
	lifeGain = new LifeGain();
	static auto red = glm::vec3(1.f, 0.f, 0.f);
	static auto yellow = glm::vec3(1.f, 1.f, 0.f);
	balloon = new Balloon(red);
	hitBalloon = new HitBalloon(red);
	balloonYellow = new Balloon(yellow);
	hitBalloonYellow = new HitBalloon(yellow);
	bowArrowCoordinates = glm::vec4(120.f, 500.f, 230.f, 500.f); //xBow, yBow, xArrow, yArrow
	yInitial = bowArrowCoordinates[1];
	resolutionY = (float)resolution.y;
	powerBarCoordinates = std::make_pair(120.f, 430.f);
	shurikens = {
		shurikenAtt((float)(rand() % 100 + 1200.f), (float)(rand() % 150 + 50.f), -(rand() % 10 + 5.f), false), // 1
		shurikenAtt((float)(rand() % 100 + 1250.f), (float)(rand() % 100 + 300.f), -(rand() % 15 + 2.f), false),
		shurikenAtt((float)(rand() % 100 + 1300.f), (float)(rand() % 100 + 500.f), -(rand() % 20 + 1.f), false)
	};

	balloons = {
		balloonAtt((float)(rand() % 100 + 550), (float)(-rand() % 250), (rand() % 10 + 5.f), false), // 1
		balloonAtt((float)(rand() % 100 + 600), (float)(-rand() % 250), (rand() % 10 + 5.f), false),
		balloonAtt((float)(rand() % 100 + 700), (float)(-rand() % 250), (rand() % 10 + 5.f), false),
		balloonAtt((float)(rand() % 100 + 800), (float)(-rand() % 250), (rand() % 10 + 5.f), false),
		balloonAtt((float)(rand() % 100 + 950), (float)(-rand() % 250), (rand() % 10 + 5.f), false),
		balloonAtt((float)(rand() % 100 + 1075), (float)(-rand() % 250), (rand() % 10 + 5.f), false),
		balloonAtt((float)(rand() % 50 + 700), (float)(-rand() % 250), (rand() % 10 + 5.f), false),
		balloonAtt((float)(rand() % 50 + 1000), (float)(-rand() % 250), (rand() % 10 + 5.f), false)
	};

	numBalloons = balloons.size();
	isBowHit = std::vector<bool>(numShurikens, false);
	lga = new lifeGainAtt((float)(rand() % 550 + 200.f), (float)(rand() % 100 + 1300.f), -(rand() % 10 + 2.f), false);
}


void Tema1::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds)
{	
	if (livesLeft > 0) {
		if ((score % 1000) == 0 && (score > 0)) {
			lifeGainActive = true;
		}

		if (lifeGainActive) {
			lga->yLifeGain += lga->speed * 80 * deltaTimeSeconds;
			if (!lga->hit) {
				if (lga->yLifeGain < -60) {
					lga->xLifeGain = (float)(rand() % 550 + 200.f);
					lga->yLifeGain = (float)(rand() % 100 + 1300.f);
					lga->speed = -(float)(rand() % 10 + 2.f);
				}
			} else {
				lifeGainActive = false;
				lga->xLifeGain = (float)(rand() % 550 + 200.f);
				lga->yLifeGain = (float)(rand() % 100 + 1300.f);
				lga->speed = -(float)(rand() % 10 + 2.f);
				lga->hit = false;
			}
		}

		if (isReleased) {
			bowArrowCoordinates[2] += glm::cos(mouseAngle.second) * arrowSpeed * 80 * deltaTimeSeconds;
			bowArrowCoordinates[3] += glm::sin(mouseAngle.second) * arrowSpeed * 80 * deltaTimeSeconds;
		}

		if (bowArrowCoordinates[2] > 1360 || bowArrowCoordinates[3] > 800 || bowArrowCoordinates[3] < -80) {
			bowArrowCoordinates[2] = bowArrowCoordinates[0] + 110.f;
			bowArrowCoordinates[3] = bowArrowCoordinates[1];
			isReleased = false;
			mouseAngle.second = INT_MIN;
		}

		for (int i = 0; i < numShurikens; ++i) {
			shurikens[i].xShuriken += shurikens[i].speed * 80 * deltaTimeSeconds;

			if (!shurikens[i].hit) {
				if (shurikens[i].xShuriken < 0) {
					shurikens[i].xShuriken = (float)(rand() % 100 + 1200.f);
					shurikens[i].speed = -(float)(rand() % 5 + 5.f);
					shurikens[i].yShuriken = (float)(rand() % 500 + 100.f);
					isBowHit[i] = false;
				}
			} else {
				if (shurikens[i].yShuriken < -20) {
					shurikens[i].hit = false;
					shurikens[i].xShuriken = (float)(rand() % 100 + 1200.f);
					shurikens[i].speed = -(float)(rand() % 5 + 5.f);
					shurikens[i].yShuriken = (float)(rand() % 500 + 100.f);
					isBowHit[i] = false;
				} else {
					shurikens[i].yShuriken += shurikens[i].speed * 80 * deltaTimeSeconds;
				}
			}
		}

		// Check shuriken colliision with bow/arrow
		CheckShurikenCollision();

		for (int i = 0; i < numBalloons; ++i) {
			balloons[i].yBalloon += balloons[i].speed;
			
			if (!balloons[i].hit) {
				if (balloons[i].yBalloon > 900) {
					balloons[i].yBalloon = (float)(-rand() % 250);
					balloons[i].speed = (rand() % 10 + 5.f) * 50 * deltaTimeSeconds;
					balloons[i].hit = false;
				}
			} else {
				if (balloons[i].yBalloon < -120) {
					balloons[i].yBalloon = (float)(-rand() % 250);
					balloons[i].xBalloon = (float)(rand() % 500 + 500);
					balloons[i].speed = (rand() % 10 + 5.f) * 50 * deltaTimeSeconds;
					balloons[i].hit = false;

				}
				else {
					balloons[i].speed = -(rand() % 10 + 5.f);
					if (i & 1) {
						balloons[i].xBalloon += balloons[i].speed;
					} else {
						balloons[i].xBalloon -= balloons[i].speed;
					}
				}
			}
		}

		// Check arrow - balloon collision
		CheckBalloonCollision();
		// Check arrow - lifeGain collision
		CheckArrowLifeGainCollision();
		// Render the objects
		RenderArrow();
		RenderBow();
		RenderPowerBar();
		RenderShuriken(deltaTimeSeconds);
		RenderHeart();
		RenderBalloon();
		RenderLifeGain(deltaTimeSeconds);
	} else {
		std::cout << "========================================================================";
		std::cout << "\n\t\t\t\tGAME OVER!\n";
		std::cout << "========================================================================\n";
		exit(EXIT_SUCCESS);
	}
}

void Tema1::FrameEnd()
{
}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
	if (window->KeyHold(GLFW_KEY_W)) {
		if (bowArrowCoordinates[1] < 620) {
			bowArrowCoordinates[1] += 400 * deltaTime;
			bowArrowCoordinates[3] += 400 * deltaTime;
			powerBarCoordinates.second += 400 * deltaTime;
			
			if (isReleased) {
				bowArrowCoordinates[3] -= 400 * deltaTime;
			}
		}

		yInitial = bowArrowCoordinates[1];
	}

	if (window->KeyHold(GLFW_KEY_S)) {
		if (bowArrowCoordinates[1] > 75) {
			bowArrowCoordinates[1] -= 400 * deltaTime;
			bowArrowCoordinates[3] -= 400 * deltaTime;
			powerBarCoordinates.second -= 400 * deltaTime;

			if (isReleased) {
				bowArrowCoordinates[3] += 400 * deltaTime;
			}
		}

		yInitial = bowArrowCoordinates[1];
	}

	if (!window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)) {
		powerScale = 1;
		powerBarScale = 1.f;
	}
	
	if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)) {
		if (!isReleased) {
			if (powerScale - MAX_POWER_SCALE < 0) {
				powerScale += 1;
				powerBarScale += 20.f * deltaTime;
				arrowSpeed = powerScale * 2.f * 80 * deltaTime;
			}
		}
	}
}

void Tema1::OnKeyPress(int key, int mods)
{
}

void Tema1::OnKeyRelease(int key, int mods)
{
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	mouseAngle.first = glm::atan((float)(resolutionY - yInitial - mouseY) / mouseX);
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
		if (mouseAngle.second == INT_MIN) {
			mouseAngle.second = mouseAngle.first;
		}
		isReleased = true;
	}
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}


void Tema1::RenderHeart() 
{
	for (int i = 0; i < livesLeft; ++i) {
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform::Translate(30.f + 50 * i, 700);
		modelMatrix *= Transform::Scale(15.f, 15.f);
		RenderMesh2D(heart->getHeart(), shaders["VertexColor"], modelMatrix);
	}
}

void Tema1::RenderArrow() 
{
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform::Translate(bowArrowCoordinates[2], bowArrowCoordinates[3]);
	modelMatrix *= Transform::Translate(-110.f, 0.f);
	if (!isReleased) {
		modelMatrix *= Transform::Rotate(mouseAngle.first);
	} else {
		modelMatrix *= Transform::Rotate(mouseAngle.second);
	}
	modelMatrix *= Transform::Translate(110.f, 0.f);
	RenderMesh2D(arrow->getArrow(), shaders["VertexColor"], modelMatrix);
}

void Tema1::RenderBow()
{
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform::Translate(bowArrowCoordinates[0], bowArrowCoordinates[1]);
	modelMatrix *= Transform::Rotate(glm::radians(-90.f));
	modelMatrix *= Transform::Rotate(mouseAngle.first);
	RenderMesh2D(bow->getBow(), shaders["VertexColor"], modelMatrix);
}

void Tema1::RenderPowerBar() 
{
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform::Translate(powerBarCoordinates.first, powerBarCoordinates.second);
	modelMatrix *= Transform::Scale(powerBarScale, 1.f);
	RenderMesh2D(powerBar->getPowerBar(), shaders["VertexColor"], modelMatrix);
}

void Tema1::RenderShuriken(float deltaTimeSeconds) 
{
	for (int i = 0; i < numShurikens; ++i) {
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform::Translate(shurikens[i].xShuriken, shurikens[i].yShuriken);
		angularStep += 200.f * deltaTimeSeconds;
		modelMatrix *= Transform::Rotate(angularStep);
		RenderMesh2D(shuriken->getShuriken(), shaders["VertexColor"], modelMatrix);
	}
}

void Tema1::RenderBalloon() 
{	
	for (int i = 0; i < numBalloons - 2; ++i) {
		if (!balloons[i].hit) {
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform::Translate(balloons[i].xBalloon, balloons[i].yBalloon);
			modelMatrix *= Transform::Scale(0.5f, 1.f);
			RenderMesh2D(balloon->getBalloon(), shaders["VertexColor"], modelMatrix);
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform::Translate(balloons[i].xBalloon, balloons[i].yBalloon);
			RenderMesh2D(balloon->getBalloonTriangle(), shaders["VertexColor"], modelMatrix);
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform::Translate(balloons[i].xBalloon, balloons[i].yBalloon);
			RenderMesh2D(balloon->getBalloonLine(), shaders["VertexColor"], modelMatrix);
		}
		else {
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform::Translate(balloons[i].xBalloon, balloons[i].yBalloon);
			modelMatrix *= Transform::Scale(0.5f, 1.f);
			RenderMesh2D(hitBalloon->getHitBalloon(), shaders["VertexColor"], modelMatrix);
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform::Translate(balloons[i].xBalloon, balloons[i].yBalloon);
			RenderMesh2D(hitBalloon->getHitBalloonTriangle(), shaders["VertexColor"], modelMatrix);
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform::Translate(balloons[i].xBalloon, balloons[i].yBalloon);
			RenderMesh2D(hitBalloon->getHitBalloonLine(), shaders["VertexColor"], modelMatrix);
		}
	}

	for (int i = numBalloons - 2; i < numBalloons; ++i) {
		if (!balloons[i].hit) {
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform::Translate(balloons[i].xBalloon, balloons[i].yBalloon);
			modelMatrix *= Transform::Scale(0.5f, 1.f);
			RenderMesh2D(balloonYellow->getBalloon(), shaders["VertexColor"], modelMatrix);
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform::Translate(balloons[i].xBalloon, balloons[i].yBalloon);
			RenderMesh2D(balloonYellow->getBalloonTriangle(), shaders["VertexColor"], modelMatrix);
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform::Translate(balloons[i].xBalloon, balloons[i].yBalloon);
			RenderMesh2D(balloonYellow->getBalloonLine(), shaders["VertexColor"], modelMatrix);
		} else {
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform::Translate(balloons[i].xBalloon, balloons[i].yBalloon);
			modelMatrix *= Transform::Scale(0.5f, 1.f);
			RenderMesh2D(hitBalloonYellow->getHitBalloon(), shaders["VertexColor"], modelMatrix);
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform::Translate(balloons[i].xBalloon, balloons[i].yBalloon);
			RenderMesh2D(hitBalloonYellow->getHitBalloonTriangle(), shaders["VertexColor"], modelMatrix);
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform::Translate(balloons[i].xBalloon, balloons[i].yBalloon);
			RenderMesh2D(hitBalloonYellow->getHitBalloonLine(), shaders["VertexColor"], modelMatrix);
		}
	}
}

void Tema1::RenderLifeGain(float deltaTimeSeconds)
{
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform::Translate(lga->xLifeGain, lga->yLifeGain);
	RenderMesh2D(lifeGain->getLifeGain(), shaders["VertexColor"], modelMatrix);
}

void Tema1::CheckArrowLifeGainCollision() 
{
	if (CheckCollision(bowArrowCoordinates[2] - 110.f - lga->xLifeGain,
		bowArrowCoordinates[3] - lga->yLifeGain, 3600.f, !lga->hit && lifeGainActive)) {
		++livesLeft;
		lifeGainActive = false;
		lga->xLifeGain = (float)(rand() % 550 + 200.f);
		lga->yLifeGain = (float)(rand() % 100 + 1300.f);
		lga->speed = -(float)(rand() % 10 + 2.f);
		lga->hit = false;
		std::cout << "************************************************************************";
		std::cout << "\n\t\t\tYou got an extra Life!\n";
		std::cout << "************************************************************************\n";
	}
}

void Tema1::CheckBalloonCollision() 
{
	for (int i = 0; i < numBalloons; ++i) {
		if (CheckCollision(bowArrowCoordinates[2] - 110.f - balloons[i].xBalloon,
			bowArrowCoordinates[3] - balloons[i].yBalloon, 7200.f, !balloons[i].hit)) {
			balloons[i].hit = true;
			if (i == 6 || i == 7) {
				score -= 50;
			}
			else {
				score += 50;
			}
			std::cout << "------------------------------------------------------------------------";
			std::cout << "\n\t\t\tYour score is: " << score << '\n';
			std::cout << "------------------------------------------------------------------------\n";
		}
	}
}

void Tema1::CheckShurikenCollision() 
{
	for (int i = 0; i < numShurikens; ++i) {
		// Check arrow - shuriken collision

		if (CheckCollision(bowArrowCoordinates[2] - 110.f - shurikens[i].xShuriken, 
			bowArrowCoordinates[3] - shurikens[i].yShuriken, 850.f, !shurikens[i].hit)) {
			shurikens[i].hit = true;
			score += 100;
			std::cout << "------------------------------------------------------------------------";
			std::cout << "\n\t\t\tYour score is: " << score << '\n';
			std::cout << "------------------------------------------------------------------------\n";
		}

		// Check bow - shuriken collision

		if (CheckCollision(bowArrowCoordinates[0] - shurikens[i].xShuriken, 
			bowArrowCoordinates[1] - shurikens[i].yShuriken, 7774.f, !shurikens[i].hit && !isBowHit[i])) {
			--livesLeft;
			isBowHit[i] = true;
		}
	}
}

bool Tema1::CheckCollision(float x, float y, float r, bool b)
{
	return ((x * x + y * y < r) && b);
}