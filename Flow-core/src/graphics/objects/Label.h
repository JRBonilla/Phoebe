#pragma once

#include "RenderObject.h"
#include "../Renderer.h"

namespace fl { namespace graphics {

	class Label : public RenderObject {
	private:
		std::string m_Text;
		Font* m_Font;
	public:
		Label(const std::string& text, float x, float y, Font* font, unsigned int color);
		void Render(Renderer* renderer) const override;
		inline void SetText(const std::string& text) { m_Text = text; }
	};
	
}}
