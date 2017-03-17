#pragma warning( disable: 4244 )
#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include "../common/Common.h"

namespace ph { namespace math {

	PHOENIX_API inline float toRadians(float degrees) {
		return degrees * (M_PI / 180.0f);
	}

	PHOENIX_API inline float toDegrees(float radians) {
		return radians * (180.0f / M_PI);
	}

	PHOENIX_API inline float abs(float value) {
		if (value < 0) return -value;
		return value;
	}

}}