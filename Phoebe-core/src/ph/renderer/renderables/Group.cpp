#include "Group.h"

namespace ph { namespace renderer {

	Group::Group(const math::Mat4& transform)
		: m_TransformationMatrix(transform) { }

	Group::~Group() {
		for (uint i = 0; i < m_Children.size(); i++) {
			delete m_Children[i];
		}
	}

	void Group::Add(Renderable2D* renderable) {
		m_Children.push_back(renderable);
	}

	void Group::Submit(Renderer2D* renderer) const {
		renderer->PushMatrix(m_TransformationMatrix);
		for (Renderable2D* child : m_Children) {
			child->Submit(renderer);
		}
		renderer->PopMatrix();
	}

}}