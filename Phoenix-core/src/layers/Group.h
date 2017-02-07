#pragma once

#include <vector>
#include "../graphics/objects/RenderObject.h"

namespace ph { namespace graphics {

	class Group : public RenderObject {
	private:
		std::vector<RenderObject*> m_Children; // The groups children
		math::mat4 m_TransformationMatrix;
	public:
		Group(const math::mat4& transform);
		~Group();
		void Add(RenderObject* object);
		void Render(Renderer* renderer) const override;
	};
	
}}
