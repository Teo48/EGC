#pragma once
#ifndef __BOW_H__
#define __BOW_H__

#include <Core/Engine.h>

class Bow {
	public:
		Bow();
		~Bow();
		Mesh* getBow();
	private:
		Mesh* bow;
};
#endif // __BOW_H__
