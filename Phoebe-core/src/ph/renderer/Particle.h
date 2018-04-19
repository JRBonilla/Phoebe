#pragma once

#include "ph/math/Vec3.h"
#include "ph/math/Vec4.h"

namespace ph { namespace renderer {

	struct Particle {
		math::Vec3 position;
		math::Vec3 velocity;
		math::Vec4 color;
		float life;

		Particle(const math::Vec3& position, const math::Vec3& velocity, const math::Vec4& color, float life = 1.0f)
			: position(position), velocity(velocity), color(color), life(life) {
		}
	};

}}