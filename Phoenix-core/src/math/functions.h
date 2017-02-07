#pragma warning( disable: 4244 )
#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

namespace ph { namespace math {

	inline float toRadians(float degrees) {
		return degrees * (M_PI / 180.0f);
	}

	inline float toDegrees(float radians) {
		return radians * (180.0f / M_PI);
	}
	
	inline float abs(float value) {
		if (value < 0) return -value;
		return value;
	}
}}