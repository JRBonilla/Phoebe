#include "FontManager.h"

namespace fl{ namespace graphics {

	std::vector<Font*> FontManager::s_Fonts;
	math::vec2 FontManager::s_Scale = math::vec2(1.0f, 1.0f);

	void FontManager::Init() {
		SetScale(math::vec2(40, 40));
		Add(new Font("Default", "res/SourceSansPro-Light.ttf", 32));
	}


	void FontManager::Add(Font* font) {
		font->SetScale(s_Scale);
		s_Fonts.push_back(font);
	}

	Font* FontManager::Get()
	{
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
	
	void FontManager::SetScale(const math::vec2& scale) {
		s_Scale = scale;
	}

}}