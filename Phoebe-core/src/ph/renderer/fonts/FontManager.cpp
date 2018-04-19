#include "FontManager.h"

namespace ph{ namespace renderer {

	std::vector<Font*> FontManager::s_Fonts;
	math::Vec2         FontManager::s_Scale = math::Vec2(1.0f, 1.0f);

	void FontManager::Init() {
		SetScale(math::Vec2(42, 42));
		Add(new Font("Default", "res/SourceSansPro-Light.ttf", 18));
	}

	void FontManager::Add(Font* font) {
		font->SetScale(s_Scale);
		s_Fonts.push_back(font);
	}

	Font* FontManager::Get() {
		return s_Fonts[0];
	}

	Font* FontManager::Get(const std::string& name) {
		for (Font* font : s_Fonts) {
			if (font->GetName() == name) {
				return font;
			}
		}
		return nullptr;
	}

	void FontManager::Clean() {
		for (uint i = 0; i < s_Fonts.size(); i++) {
			delete s_Fonts[i];
		}
	}
	
	void FontManager::SetScale(const math::Vec2& scale) {
		s_Scale = scale;
	}

}}