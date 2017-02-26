#include "Label.h"

namespace ph { namespace graphics {

	Label::Label(const std::string& text, float x, float y, Font* font, const vec4& color)
		: Renderable(), m_Text(text), m_Font(font) {
		m_Position = vec3(x, y, 0.0f);

		int r = color.x * 255.0f;
		int g = color.y * 255.0f;
		int b = color.z * 255.0f;
		int a = color.w * 255.0f;
		m_Color = a << 24 |	b << 16 | g << 8 | r;
	}

	void Label::Render(Renderer* renderer) const {
		renderer->DrawString(m_Text.c_str(), m_Position, *m_Font, m_Color);
	}


}}