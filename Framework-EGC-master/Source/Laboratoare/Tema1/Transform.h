#pragma once
#include <include/glm.h>

namespace Transform
{
	// Translate matrix
	inline glm::mat3 Translate(float translateX, float translateY)
	{
		// TODO implement translate matrix
		return glm::mat3(
			1.f, 0.f, 0.f,
			0.f, 1.f, 0.f,
			translateX, translateY, 1.f);
	}

	// Scale matrix
	inline glm::mat3 Scale(float scaleX, float scaleY)
	{
		// TODO implement scale matrix

		return glm::mat3(
			scaleX, 0.f, 0.f,
			0.f, scaleY, 0.f,
			0.f, 0.f, 1.f
		);
	}

	// Rotate matrix
	inline glm::mat3 Rotate(float radians)
	{
		// TODO implement rotate matrix
		auto sine = glm::sin(radians);
		auto cosine = glm::cos(radians);

		return glm::mat3(
			cosine, sine, 0.f,
			-sine, cosine, 0.f,
			0.f, 0.f, 1.f
		);
	}
}
