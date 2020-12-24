#pragma once
#ifndef __TRANSFORM3_H__
#define __TRANSFORM3_H__

#pragma once

#include <include/glm.h>

namespace Transform3D
{	
	inline glm::mat3 Translate2D(float translateX, float translateY)
	{
		// TODO implement translate matrix
		return glm::mat3(
			1.f, 0.f, 0.f,
			0.f, 1.f, 0.f,
			translateX, translateY, 1.f);
	}

	// Scale matrix
	inline glm::mat3 Scale2D(float scaleX, float scaleY)
	{
		// TODO implement scale matrix

		return glm::mat3(
			scaleX, 0.f, 0.f,
			0.f, scaleY, 0.f,
			0.f, 0.f, 1.f
		);
	}

	// Translate matrix
	inline glm::mat4 Translate(float translateX, float translateY, float translateZ)
	{
		// TODO implement translate matrix
		return glm::transpose(glm::mat4(1, 0, 0, translateX,
			0, 1, 0, translateY,
			0, 0, 1, translateZ,
			0, 0, 0, 1));
	}

	// Scale matrix
	inline glm::mat4 Scale(float scaleX, float scaleY, float scaleZ)
	{
		// TODO implement scale matrix
		return glm::transpose(glm::mat4(scaleX, 0, 0, 0,
			0, scaleY, 0, 0,
			0, 0, scaleZ, 0,
			0, 0, 0, 1));
	}

	// Rotate matrix relative to the OZ axis
	inline glm::mat4 RotateOZ(float radians)
	{
		// TODO implement rotate matrix
		static auto c = glm::cos(radians);
		static auto s = glm::sin(radians);

		return glm::transpose(glm::mat4(c, -s, 0, 0,
			s, c, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1));
	}

	// Rotate matrix relative to the OY axis
	inline glm::mat4 RotateOY(float radians)
	{
		// TODO implement rotate matrix
		static auto c = glm::cos(radians);
		static auto s = glm::sin(radians);

		return glm::transpose(glm::mat4(c, 0, s, 0,
			0, 1, 0, 0,
			-s, 0, c, 0,
			0, 0, 0, 1));
	}

	// Rotate matrix relative to the OX axis
	inline glm::mat4 RotateOX(float radians)
	{
		// TODO implement rotate matrix
		static auto c = glm::cos(radians);
		static auto s = glm::sin(radians);

		return glm::transpose(glm::mat4(1, 0, 0, 0,
			0, c, -s, 0,
			0, s, c, 0,
			0, 0, 0, 1));
	}
}


#endif // __TRANSFORM3_H__
