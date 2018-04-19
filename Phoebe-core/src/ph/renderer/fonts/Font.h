#pragma once

#include "FontAtlas.h"
#include "../Texture2D.h"
#include "ph/math/Math.h"

namespace ph { namespace renderer {

	class Font {
	private:
		FT_Library     m_FTLibrary;
		FT_Face        m_FTFace;
		FontAtlas*     m_FontAtlas;
		float          m_Size;
		math::Vec2     m_Scale;
		std::string    m_Name;
		std::string    m_Filename;
	public:
		Font(const std::string& name, const std::string& filename, float size);
		~Font();

		inline const math::Vec2& GetScale() const { return m_Scale; }
		inline void SetScale(const math::Vec2& scale) { m_Scale = scale; }

		inline const std::string& GetFilename() const { return m_Filename; }
		inline const std::string& GetName()     const { return m_Name; }
		inline const float        GetSize()     const { return m_Size; }

		inline FontAtlas* GetTextureAtlas() const { return m_FontAtlas; }
		inline Texture2D* GetTexture()      const { return m_FontAtlas->texture; }
	};
	
}}
