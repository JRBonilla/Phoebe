#pragma once

#include <vector>
#include "../graphics/renderables/Renderable.h"

namespace ph { namespace graphics {

	class Group : public Renderable {
	private:
		std::vector<Renderable*> m_Children; // The groups children
		math::mat4 m_TransformationMatrix;
	public:
		Group(const math::mat4& transform);
		~Group();
		void Add(Renderable* renderable);
		void Render(Renderer* renderer) const override;
	};
	
}}
