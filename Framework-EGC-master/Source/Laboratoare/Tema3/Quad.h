#pragma once
#include <Core\Engine.h>
#ifndef __QUAD_H__
#define __QUAD_H__

class Quad {
	public:
		Quad();
		~Quad();
		Mesh* getQuad();
	private:
		Mesh* quad;
};

#endif // __QUAD_H__