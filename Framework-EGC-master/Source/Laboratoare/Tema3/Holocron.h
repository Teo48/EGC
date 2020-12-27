#pragma once
#ifndef __HOLOCRON_H__
#define __HOLOCORN_H__

#include <Core/Engine.h>

class Holocron {
	public:
		Holocron();
		~Holocron();
		void Init();
		
		typedef enum { jedi = 0, sith = 1 } HOLOCRON_TYPES;
		typedef struct attributes {
			float xmin;
			float xmax;
			float ymin;
			float ymax;
			float zmin;
			float zmax;
			int type;
			int collide;
			int collumn;
			int line;
		} attributes;

		attributes att;
		std::vector<attributes> holocrons;

		Mesh* getJediHolocron();
		Mesh* getSithHolocron();
	private:
		Mesh* jediHolocron;
		Mesh* sithHolocron;
};

#endif // __HOLOCRON_H__
