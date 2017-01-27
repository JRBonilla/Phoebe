#pragma once

#include <vector>
#include "../objects/RenderObject.h"

namespace fl { namespace graphics {

	class Group : public RenderObject
	{
	private:
		std::vector<RenderObject*> m_Children; // The groups children
		math::mat4 m_TransformationMatrix;
	public:
		Group(const math::mat4& transform);
		~Group();
		void add(RenderObject* renderable);
		void Render(Renderer* renderer) const override;
	};
	
}}
