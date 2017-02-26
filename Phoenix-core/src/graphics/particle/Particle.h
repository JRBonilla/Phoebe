#pragma once

#include "../../math/math.h"
#include "../../common/Types.h"

namespace ph { namespace graphics {

	struct Particle {
		math::vec2 position, velocity;
		uint color;
		float size, angle, weight;
		float life;
	};

}}