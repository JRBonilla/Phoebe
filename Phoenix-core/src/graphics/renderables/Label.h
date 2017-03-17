#pragma once

#include "Renderable.h"
#include "../Renderer.h"

namespace ph { namespace graphics {

	class Label : public Renderable {
	private:
		Font*		m_Font;
		std::string m_Text;
	public:
		Label(const std::string& text, float x, float y, Font* font, const Vec4& color);

		void Render(Renderer* renderer) const override;
		inline void SetText(const std::string& text) { m_Text = text; }
	};
	
}}
