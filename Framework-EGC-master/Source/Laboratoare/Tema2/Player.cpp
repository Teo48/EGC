#include "Player.h"

Player::Player() {
	player = new Mesh("sphere");
	player->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "altgigel1.obj");
}

Player::~Player() {
	delete this->player;
}

Mesh* Player::getPlayer() {
	return this->player;
}