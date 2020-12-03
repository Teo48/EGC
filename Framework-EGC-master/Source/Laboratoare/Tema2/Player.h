#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <Core/Engine.h>

class Player {
	public:
		Player();
		~Player();
		Mesh* getPlayer();
	private:
		Mesh* player;
};

#endif // __PLAYER_H__