#pragma once

#include <string>
#include <glad/glad.h>
#include "Texture.h"
#include "ph/Types.h"
#include "ph/utils/Image.h"
#include "ph/utils/Log.h"

namespace ph { namespace renderer {

	class Texture2D : public Texture {
	private:
		std::string         m_Name;
		std::string         m_Filename;
		uint                m_TextureID;
		uint                m_Width, m_Height;
		TextureParameters   m_Parameters;
		TextureLoadOptions  m_LoadOptions;
	public:
		Texture2D(const std::string& name, const std::string& filename, bool byteAlignment = false, TextureParameters parameters = TextureParameters(), TextureLoadOptions loadOptions = TextureLoadOptions());
		Texture2D(uint width, uint height, bool byteAlignment = false, TextureParameters parameters = TextureParameters(), TextureLoadOptions loadOptions = TextureLoadOptions());
		~Texture2D();

		void SetData(byte* pixels, uint xoffset, uint yoffset, uint width, uint height);

		void Bind(uint slot)   const override;
		void Unbind(uint slot) const override;

		inline const std::string& GetName() const { return m_Name; }
		inline const uint GetID() const { return m_TextureID; }
		inline int GetWidth()  const { return m_Width; }
		inline int GetHeight() const { return m_Height; }
	private:
		uint Load(bool byteAlignment = false);
	};

}}