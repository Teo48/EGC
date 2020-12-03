#pragma once
#ifndef __CUBE_H__
#define __CUBE_H__

#include <Core/Engine.h>

class Cube {
	public:
		Cube();
		~Cube();
		Mesh* getCube();
		typedef enum {blue = 0, dark_blue = 1, red = 2, yellow = 3, orange = 4, green = 5, black = 6} COLORS;
		typedef struct attributes {
			float xmin;
			float xmax;
			float ymin;
			float ymax;
			float zmin;
			float zmax;
			float length;
			int color;
			int collide;
		} attributes;
		int pickColor();
		void Init();
		std::vector<std::vector<attributes>> cubes;
		float randomFloat(const float min, const float max);
private:
		Mesh* cube;
};

#endif // __CUBE_H__
