#pragma once
#ifndef __FUELBAR_H__
#define __FUELBAR_H__

#include <Core/Engine.h>

class FuelBar {
public:
	FuelBar();
	~FuelBar();
	Mesh* getbackgroundFuelBar();
	Mesh* getforegroundFuelBar();
private:
	Mesh* backgroundFuelBar;
	Mesh* foregroundFuelBar;
};


#endif // __FUELBAR_H__
