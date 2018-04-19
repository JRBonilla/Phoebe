#pragma once

#include <string>
#include "Texture2D.h"
#include "ph/Types.h"
#include "ph/math/Vec2.h"

namespace ph { namespace renderer {

	class TextureAtlas {
	private:
		TextureParameters  m_Parameters;
		std::string        m_Filename;
		uint               m_Width;
		uint               m_Height;
		uint               m_SubImageWidth;
		uint               m_SubImageHeight;
	public:
		TextureAtlas(const std::string& filename, uint subImageWidth, uint subImageHeight);
		~TextureAtlas();

		inline const math::Vec2& GetSize()   const { return math::Vec2((float)m_Width, (float)m_Height); }
		inline const uint        GetWidth()  const { return m_Width; }
		inline const uint        GetHeight() const { return m_Height; }

		inline uint GetSubImageWidth()  const { return m_SubImageWidth; }
		inline uint GetSubImageHeight() const { return m_SubImageHeight; }

		inline void SetSubImageWidth(uint width)   { m_SubImageWidth = width; }
		inline void SetSubImageHeight(uint height) { m_SubImageHeight = height; }
	private:
		uint Load();
	};

}}