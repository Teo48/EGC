#pragma once

#include <Component/SimpleScene.h>

constexpr int NUM_OBJECTS = 3;
constexpr float MOVEMENT_SPEED = 2.f;

class Laborator1 : public SimpleScene
{
	public:
		Laborator1();
		~Laborator1();

		void Init() override;

	private:
		glm::vec3 pixel;
		glm::vec3 coordinates;
		std::string objMeshList[NUM_OBJECTS] = {"box", "sphere", "teapot"};
		std::string chosenMeshObj = "box";
		int cntMeshObj = 1;
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
		GLclampf randomColor();
};
