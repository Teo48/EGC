#pragma once

#include <Component/SimpleScene.h>
#include <Core/Engine.h>
#include "Arrow.h"
#include "Bow.h"
#include "Shuriken.h"
#include "PowerBar.h"
#include "Heart.h"
#include "Balloon.h"
#include "HitBalloon.h"
#include "LifeGain.h"

class Tema1 : public SimpleScene
{
public:
	Tema1();
	~Tema1();

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;
	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;
	inline void RenderHeart();
	inline void RenderPowerBar();
	inline void RenderBalloon();
	inline void RenderHitBalloon();
	inline void RenderBow();
	inline void RenderArrow();
	inline void RenderShuriken(float deltaTimeSeconds);
	inline void RenderLifeGain(float deltaTimeSeconds);
	inline void CheckArrowLifeGainCollision();
	inline void CheckBalloonCollision();
	inline void CheckShurikenCollision();
	inline bool CheckCollision(const float x, const float y, const float r, const bool b);

protected:
	Arrow* arrow;
	Bow* bow;
	Shuriken* shuriken;
	PowerBar* powerBar;
	Heart* heart;
	Balloon* balloon;
	Balloon* balloonYellow;
	HitBalloon* hitBalloon;
	HitBalloon* hitBalloonYellow;
	LifeGain* lifeGain;
	glm::mat3 modelMatrix;
	GLenum cullFace;
	GLenum polygonMode;
	int livesLeft;
	glm::vec4 bowArrowCoordinates;
	std::pair<float, float> powerBarCoordinates;
	std::pair<GLfloat, GLfloat> mouseAngle;
	int numShurikens;
	int numBalloons;
	bool isReleased;
	bool lifeGainActive;
	int powerScale;
	int MAX_POWER_SCALE = 30.f;
	float yInitial;
	long score = 0;
	GLfloat powerBarScale = 1.f;
	GLfloat arrowSpeed = 15.f;
	GLfloat angularStep;
	GLfloat resolutionY;
	GLfloat arrowY;

	typedef struct shurikenAtt {
		float xShuriken;
		float yShuriken;
		float speed;
		bool hit;

		shurikenAtt(const float xShuriken, const float yShuriken, 
					const float speed, const bool hit) {
			this->xShuriken = xShuriken;
			this->yShuriken = yShuriken;
			this->speed = speed;
			this->hit = hit;
		}
	} shurikenAtt;

	typedef struct balloonAtt {
		float xBalloon;
		float yBalloon;
		float speed;
		bool hit;

		balloonAtt(const float xBalloon, const float yBalloon,
					const float speed, const bool hit) {
			this->xBalloon = xBalloon;
			this->yBalloon = yBalloon;
			this->speed = speed;
			this->hit = hit;
		}
	};

	typedef struct lifeGainAtt {
		float xLifeGain;
		float yLifeGain;
		float speed;
		bool hit;
		lifeGainAtt() {}

		lifeGainAtt(const float xLifeGain, const float yLifegain,
				const float speed, const bool hit) {
			this->xLifeGain = xLifeGain;
			this->yLifeGain = yLifeGain;
			this->speed = speed;
			this->hit = hit;
		}
	};

	lifeGainAtt *lga;

	std::vector<shurikenAtt> shurikens;
	std::vector<balloonAtt> balloons;
	std::vector<bool> isBowHit;
};
