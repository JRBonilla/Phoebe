#include "Renderable.h"

namespace ph { namespace graphics {

	Renderable::Renderable()
		: m_Texture(nullptr), m_UV(GetDefaultUVs()) { }

	Renderable::Renderable(const Vec3& position, const Vec2& size, uint color)
		: m_Position(position), m_Size(size), m_Color(color), m_Texture(nullptr), m_UV(GetDefaultUVs()) { }
	
	Renderable::~Renderable() { }

	void Renderable::Render(Renderer* renderer) const {
		renderer->PushRenderable(this);
	}
	
	const std::vector<math::Vec2>& Renderable::GetDefaultUVs() {
		static std::vector<math::Vec2> results;
		if (!results.size()) {
			results.push_back(math::Vec2(0, 0));
			results.push_back(math::Vec2(0, 1));
			results.push_back(math::Vec2(1, 1));
			results.push_back(math::Vec2(1, 0));
		}
		return results;
	}

}}