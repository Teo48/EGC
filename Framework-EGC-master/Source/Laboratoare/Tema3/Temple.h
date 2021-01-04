#pragma once
#ifndef __TEMPLE_H__
#define __TEMPLE_H__

#include <Core\Engine.h>

class Temple {
public:
	Temple();
	~Temple();
	Mesh* getTemple();
private:
	Mesh* temple;
};
#endif // __TEMPLE_H__
