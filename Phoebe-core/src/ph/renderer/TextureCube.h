#pragma once

#include <string>
#include <glad/glad.h>
#include "Texture.h"
#include "ph/Types.h"
#include "ph/utils/Image.h"

namespace ph { namespace renderer {

	class TextureCube : public Texture {
	private:
		enum class Layout {
			VERTICAL_CROSS,
			HORIZONTAL_CROSS
		};
	private:
		TextureParameters   m_Parameters;
		TextureLoadOptions  m_LoadOptions;
		Layout              m_Layout;
		std::string         m_Name;
		std::string*        m_Files;
		uint                m_TextureID;
		uint                m_Width, m_Height;
		uint                m_Bits;
	public:
		TextureCube(const std::string& name, const std::string& filename);
		TextureCube(const std::string& name, const std::string* files);
		TextureCube(const std::string& name, const std::string* files, uint mips, Layout layout);
		~TextureCube();

		void Bind(uint slot)   const override;
		void Unbind(uint slot) const override;

		inline const Layout GetLayout() const { return m_Layout; }
		inline const uint   GetID()     const { return m_TextureID; }

		inline uint GetWidth()  const { return m_Width; }
		inline uint GetHeight() const { return m_Height; }
	private:
		uint LoadFromFile();
		uint LoadFromFiles();
		uint LoadFromVerticalCross(uint mips);
		uint LoadFromHorizontalCross(uint mips);
	};

}}