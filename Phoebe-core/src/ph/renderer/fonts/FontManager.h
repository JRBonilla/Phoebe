#pragma once

#include <vector>
#include "Font.h"

namespace ph { namespace renderer {

	class FontManager {
	private:
		static std::vector<Font*> s_Fonts;
		static math::Vec2 s_Scale;
	public:
		static void Init();

		static void SetScale(const math::Vec2& scale);
		static inline const math::Vec2& GetScale() { return s_Scale; }

		static void  Add(Font* font);
		static Font* Get();
		static Font* Get(const std::string& name);
		static void  Clean();
	private:
		FontManager() { }
	};

}}