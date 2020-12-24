#pragma once
#ifndef  __HEART_H__
#define __HEART_H__

#include <Core/Engine.h>

class Heart {
	public:
		Heart();
		~Heart();
		Mesh* getHeart();
	private:
		Mesh* heart;
};

#endif //  __HEART_H__

