#include "Label.h"

namespace fl { namespace graphics {

	Label::Label(const std::string& text, float x, float y, Font* font, unsigned int color)
		: RenderObject(), m_Text(text), m_Font(font)
	{
		m_Position = vec3(x, y, 0.0f);
		m_Color = color;
	}

	void Label::Render(Renderer* renderer) const
	{
		renderer->DrawString(m_Text.c_str(), m_Position, *m_Font, m_Color);
	}


}}