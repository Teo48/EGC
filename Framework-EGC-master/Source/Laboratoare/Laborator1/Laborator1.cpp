#include "Laborator1.h"

#include <vector>
#include <iostream>
#include <time.h>
#include <Core/Engine.h>

using namespace std;

// Order of function calling can be seen in "Source/Core/World.cpp::LoopUpdate()"
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/World.cpp

Laborator1::Laborator1()
{
}

Laborator1::~Laborator1()
{
}

void Laborator1::Init()
{
	srand(time(nullptr));
	// Load a mesh from file into GPU memory
	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		Mesh* sphereMesh = new Mesh("sphere");
		sphereMesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		Mesh* teapotMesh = new Mesh("teapot");
		teapotMesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "teapot.obj");
		meshes[mesh->GetMeshID()] = mesh;
		meshes[sphereMesh->GetMeshID()] = sphereMesh;
		meshes[teapotMesh->GetMeshID()] = teapotMesh;
	}
}

void Laborator1::FrameStart()
{

}

void Laborator1::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->props.resolution;

	// sets the clear color for the color buffer
	glClearColor(get<0>(pixel),
				get<1>(pixel),
				get<2>(pixel), 1);

	// clears the color buffer (using the previously set color) and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);

	// render the object
	RenderMesh(meshes["box"], glm::vec3(1, 0.5f, 0), glm::vec3(0.5f));

	// render the object again but with different properties
	RenderMesh(meshes["box"], glm::vec3(-1, 0.5f, 0));
	
	// render 3rd object
	RenderMesh(meshes[chosenMeshObj], glm::vec3(get<0>(coordinates), 
						get<1>(coordinates), 
						get<2>(coordinates)));
}

void Laborator1::FrameEnd()
{
	DrawCoordinatSystem();
}

// Read the documentation of the following functions in: "Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Laborator1::OnInputUpdate(float deltaTime, int mods)
{
	// treat continuous update based on input

	if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
		if (window->KeyHold(GLFW_KEY_W)) {
			get<2>(coordinates) -= MOVEMENT_SPEED * deltaTime;
		}

		if (window->KeyHold(GLFW_KEY_S)) {
			get<2>(coordinates) += MOVEMENT_SPEED * deltaTime;
		}

		if (window->KeyHold(GLFW_KEY_D)) {
			get<0>(coordinates) += MOVEMENT_SPEED * deltaTime;
		}

		if (window->KeyHold(GLFW_KEY_A)) {
			get<0>(coordinates) -= MOVEMENT_SPEED * deltaTime;
		}

		if (window->KeyHold(GLFW_KEY_E)) {
			get<1>(coordinates) += MOVEMENT_SPEED * deltaTime;
		}

		if (window->KeyHold(GLFW_KEY_Q)) {
			get<1>(coordinates) -= MOVEMENT_SPEED * deltaTime;
		}
	}
};

void Laborator1::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_F) {
		// update the clear color randomly
		get<0>(pixel) = randomColor();
		get<1>(pixel) = randomColor();
		get<2>(pixel) = randomColor();
	}

	if (key == GLFW_KEY_R) {
		chosenMeshObj = objMeshList[cntMeshObj++ % 3];
	}
};

void Laborator1::OnKeyRelease(int key, int mods)
{
	// add key release event
};

void Laborator1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
};

void Laborator1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
};

void Laborator1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
	// treat mouse scroll event
}

void Laborator1::OnWindowResize(int width, int height)
{
	// treat window resize event
}

GLclampf Laborator1::randomColor()
{
	return ((GLclampf)rand() / (RAND_MAX));
}
