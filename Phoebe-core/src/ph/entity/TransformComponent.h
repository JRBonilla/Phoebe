#pragma once

#include "Component.h"
#include "ph/math/Mat4.h"

namespace ph { namespace entity {

	class TransformComponent : public Component {
	public:
		math::Mat4 transform;
	public:
		TransformComponent(const math::Mat4& transform) : transform(transform) {}

		static ComponentType* GetStaticType() {
			static ComponentType type({ "Transform" });
			return &type;
		}

		inline virtual ComponentType* GetType() const override { return GetStaticType(); }
	};

}}