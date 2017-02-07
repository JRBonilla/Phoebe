#include "Group.h"

namespace ph { namespace graphics {

	Group::Group(const math::mat4& transform)
		: m_TransformationMatrix(transform) { }

	Group::~Group() {
		for (uint i = 0; i < m_Children.size(); i++) {
			delete m_Children[i];
		}
	}

	void Group::Add(RenderObject* object) {
		m_Children.push_back(object);
	}

	void Group::Render(Renderer* renderer) const {
		renderer->PushMatrix(m_TransformationMatrix);
		for (RenderObject* child : m_Children) {
			child->Render(renderer);
		}
		renderer->PopMatrix();
	}

}}