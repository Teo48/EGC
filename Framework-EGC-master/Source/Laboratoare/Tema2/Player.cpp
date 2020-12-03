#include "Player.h"

Player::Player() {
	player = new Mesh("sphere");
	player->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
}

Player::~Player() {
	delete this->player;
}

Mesh* Player::getPlayer() {
	return this->player;
}