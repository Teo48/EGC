#pragma once
#ifndef __BALLOON_H__
#define __BALLOON_H__

#include <Core/Engine.h>

class Balloon {
	public: 
		Balloon(glm::vec3 &color);
		~Balloon();
		Mesh* getBalloon();
		Mesh* getBalloonLine();
		Mesh* getBalloonTriangle();
	private:
		Mesh* balloon;
		Mesh* balloonLine;
		Mesh* balloonTriangle;
};
#endif // __BALLOON_H__
