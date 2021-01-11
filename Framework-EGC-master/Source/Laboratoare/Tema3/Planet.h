#ifndef __PLANET_H__
#define __PLANET_H__

#include <Core\Engine.h>

class Planet {
public:
	Planet();
	~Planet();
	Mesh* getPlanet();
private:
	Mesh* planet;
};

#endif // __PLANET_H__
