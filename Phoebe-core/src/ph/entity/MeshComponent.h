#pragma once

#include "Component.h"
#include "ph/renderer/Mesh.h"

namespace ph { namespace entity {

	class MeshComponent : public Component {
	public:
		renderer::Mesh* mesh;
	public:
		MeshComponent(renderer::Mesh* mesh) : mesh(mesh) {}

		static ComponentType* GetStaticType() {
			static ComponentType type({ "Mesh" });
			return &type;
		}

		inline virtual ComponentType* GetType() const override { return GetStaticType(); }
	};

}}