#pragma once

#include <vector>
#include "Renderable2D.h"

namespace ph { namespace renderer {

	class Group : public Renderable2D {
	private:
		std::vector<Renderable2D*> m_Children; // The group's children
		math::Mat4                 m_TransformationMatrix;
	public:
		Group(const math::Mat4& transform);
		~Group();

		void Add(Renderable2D* renderable);
		void Submit(Renderer2D* renderer) const override;
	};
	
}}
