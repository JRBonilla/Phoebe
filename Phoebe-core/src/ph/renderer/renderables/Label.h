#pragma once

#include "Renderable2D.h"
#include "../Renderer2D.h"

namespace ph { namespace renderer {

	class Label : public Renderable2D {
	private:
		std::string m_Text;
		Font*       m_Font;
	public:
		Label(const std::string& text, float x, float y, Font* font, const math::Vec4& color);

		void Submit(Renderer2D* renderer) const override;
		inline void SetText(const std::string& text) { m_Text = text; }
	};
	
}}
