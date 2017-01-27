#include "Group.h"

namespace fl { namespace graphics {

	Group::Group(const math::mat4& transform)
		: m_TransformationMatrix(transform)
	{
	}

	Group::~Group()
	{
		for (uint i = 0; i < m_Children.size(); i++)
		{
			delete m_Children[i];
		}
	}


	void Group::add(RenderObject* renderable)
	{
		m_Children.push_back(renderable);
	}


	void Group::Render(Renderer* renderer) const
	{
		renderer->PushMatrix(m_TransformationMatrix);
		for (RenderObject* child : m_Children)
		{
			child->Render(renderer);
		}
		renderer->PopMatrix();
	}


}}