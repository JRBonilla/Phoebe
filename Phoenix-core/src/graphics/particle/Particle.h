#pragma once

#include "../../math/PhoenixMath.h"
#include "../../common/Types.h"

namespace ph { namespace graphics {

	struct Particle {
		math::Vec2 position, velocity;
		uint color;
		float size, angle, weight;
		float life;
	};

}}