#pragma warning( disable: 4244 )
#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include "ph/Common.h"

#define F_PI 3.14159265358f

namespace ph { namespace math {

	PHOEBE_API FORCE_INLINE float toRadians(float degrees) {
		return degrees * (F_PI / 180.0f);
	}

	PHOEBE_API FORCE_INLINE float toDegrees(float radians) {
		return radians * (180.0f / F_PI);
	}

	PHOEBE_API FORCE_INLINE float abs(float value) {
		return value < 0 ? -value : value;
	}

	PHOEBE_API FORCE_INLINE float rsqrt(float value) {
		return 1.0f / ::sqrt(value);
	}

	PHOEBE_API FORCE_INLINE float clamp(float x, float min, float max) {
		return (x < min) ? min : (x > max) ? max : x;
	}

}}