#include "Renderable2D.h"

namespace ph { namespace renderer {

	using namespace math;

	Renderable2D::Renderable2D()
		: m_Texture(nullptr), m_UVs(GetDefaultUVs()) {
	}

	Renderable2D::Renderable2D(const Vec3& position, const Vec2& size, uint color)
		: m_Position(position), m_Size(size), m_Color(color), m_Texture(nullptr), m_UVs(GetDefaultUVs()) {
		m_Bounds = Rectangle(position.x, position.y, size.x, size.y);
	}
	
	Renderable2D::~Renderable2D() {
	}

	void Renderable2D::Submit(Renderer2D* renderer) const {
		renderer->Submit(this);
	}
	
	const std::vector<math::Vec2>& Renderable2D::GetDefaultUVs() {
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