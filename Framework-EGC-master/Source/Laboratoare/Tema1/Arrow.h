#pragma once
#ifndef __ARROW_H__
#define __ARROW_H__

#include <Core/Engine.h>

class Arrow {
	public:
		Arrow();
		~Arrow();
		Mesh* getArrow();
	private:
		Mesh* arrow;
};

#endif __ARROW_H__