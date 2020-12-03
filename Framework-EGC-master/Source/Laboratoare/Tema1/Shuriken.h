#pragma once
#ifndef __SHURIKEN_H__
#define __SHURIKEN_H__

#include <Core/Engine.h>

class Shuriken {
	public:
		Shuriken();
		~Shuriken();
		Mesh* getShuriken();
	private:
		Mesh* shuriken;
};

#endif // __SHURIKEN_H__
