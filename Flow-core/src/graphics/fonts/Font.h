#pragma once

#include "FontStructures.h"
#include "../Texture.h"
#include "../../math/Math.h"

namespace fl { namespace graphics {

	class Font {
	private:
		float m_Size;
		math::vec2 m_Scale;
		std::string m_Name;
		std::string m_Filename;
		FontTextureAtlas* m_FTAtlas;
		FT_Library m_FTLibrary;
		FT_Face m_FTFace;
	public:
		Font(const std::string& name, const std::string& filename, float size);
		~Font();

		inline void SetScale(const math::vec2& scale) { m_Scale = scale; }

		inline const float GetSize() const { return m_Size; }
		inline const std::string& GetName() const { return m_Name; }
		inline const std::string& GetFilename() const { return m_Filename; }
		inline Texture* GetTexture() const { return m_FTAtlas->texture; }
		inline FontTextureAtlas* GetTextureAtlas() const { return m_FTAtlas; }
		inline const math::vec2& GetScale() const { return m_Scale; }
	};
	
}}
