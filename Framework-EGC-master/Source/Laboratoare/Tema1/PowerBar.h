#pragma once
#ifndef __POWERBAR_H__
#define __POWERBAR_H__

#include <Core/Engine.h>

class PowerBar {
	public:
		PowerBar();
		~PowerBar();
		Mesh* getPowerBar();
	private:
		Mesh* powerBar;
};

#endif // __POWERBAR_H__