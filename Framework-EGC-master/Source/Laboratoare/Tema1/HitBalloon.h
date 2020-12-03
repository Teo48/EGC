#pragma once
#ifndef __HITBALLOON_H__
#define __HITBALLOON_H__

#include <Core/Engine.h>

class HitBalloon {
	public:
		HitBalloon(glm::vec3 &color);
		~HitBalloon();
		Mesh* getHitBalloon();
		Mesh* getHitBalloonLine();
		Mesh* getHitBalloonTriangle();
	private:
		Mesh* hitBalloon;
		Mesh* hitBalloonTriangle;
		Mesh* hitBalloonLine;
};

#endif // __HITBALLOON_H__
