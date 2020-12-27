#include "Holocron.h"

Holocron::Holocron()
{
	jediHolocron = new Mesh("jediHolocron");
	jediHolocron->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "jediholocron.obj");

	sithHolocron = new Mesh("sithHolocron");
	sithHolocron->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sith.obj");
}

Holocron::~Holocron()
{
	delete this->jediHolocron;
	delete this->sithHolocron;
}

void Holocron::Init()
{
}

Mesh* Holocron::getSithHolocron()
{
	return this->sithHolocron;
}

Mesh* Holocron::getJediHolocron()
{
	return this->jediHolocron;
}
