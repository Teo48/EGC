#pragma once
#ifndef __LIFEGAIN_H__
#define __LIFEGAIN_H__
#include <Core/Engine.h>
class LifeGain {
	public:
		LifeGain();
		~LifeGain();
		Mesh* getLifeGain();
	private:
		Mesh* lifeGain;
};

#endif // __LIFEGAIN_H__
