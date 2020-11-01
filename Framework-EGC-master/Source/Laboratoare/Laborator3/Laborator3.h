#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>

constexpr float MOVE_SPEED = 0.5f;
constexpr float squareSide = 100.f;

class Laborator3 : public SimpleScene
{
	public:
		Laborator3();
		~Laborator3();

		void Init() override;

	private:
		bool up = false;
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

	protected:
		glm::mat3 modelMatrix;
		float translateX, translateY;
		float scaleX, scaleY;
		float angularStep;
		long long rotateCounter = 0;
		bool leftRotate = true;
		long long scaleCounter = 0;
		bool upScale = true;
};
