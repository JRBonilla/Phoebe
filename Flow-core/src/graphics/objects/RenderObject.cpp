#include "RenderObject.h"

namespace fl { namespace graphics {
	RenderObject::RenderObject()
		: m_Texture(nullptr), m_UV(GetDefaultUVs()) { }

	RenderObject::RenderObject(const vec3& position, const vec2& size, unsigned int color)
		: m_Position(position), m_Size(size), m_Color(color), m_Texture(nullptr), m_UV(GetDefaultUVs()) { }
	
	RenderObject::~RenderObject() { }

	void RenderObject::Render(Renderer* renderer) const {
		renderer->PushRenderObject(this);
	}
	
	const std::vector<math::vec2>& RenderObject::GetDefaultUVs() {
		static std::vector<math::vec2> results;
		if (!results.size())
		{
			results.push_back(math::vec2(0, 0));
			results.push_back(math::vec2(0, 1));
			results.push_back(math::vec2(1, 1));
			results.push_back(math::vec2(1, 0));
		}
		return results;
	}

}}