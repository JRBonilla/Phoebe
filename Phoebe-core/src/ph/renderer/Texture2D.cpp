#include "Texture2D.h"

namespace ph { namespace renderer {

	Texture2D::Texture2D(const std::string& name, const std::string& path, bool byteAlignment, TextureParameters parameters, TextureLoadOptions loadOptions)
		: m_Name(name), m_Filename(path), m_Parameters(parameters), m_LoadOptions(loadOptions) {
		m_TextureID = Load(byteAlignment);
	}

	Texture2D::Texture2D(uint width, uint height, bool byteAlignment, TextureParameters parameters, TextureLoadOptions loadOptions)
		: m_Filename("NULL"), m_Width(width), m_Height(height), m_Parameters(parameters), m_LoadOptions(loadOptions) {
		m_TextureID = Load(byteAlignment);
	}

	Texture2D::~Texture2D() {
		glDeleteTextures(1, &m_TextureID);
	}

	uint Texture2D::Load(bool byteAlignment) {
		byte* pixels = nullptr;

		if (m_Filename != "NULL") {
			uint bits;
			pixels = Image::Load(m_Filename, &m_Width, &m_Height, &bits, !m_LoadOptions.flipVertical);
			if (bits != 24 && bits != 32) {
				PH_INFO("Unsupported image bit-depth! (" << bits << ")");
			}
			m_Parameters.format = (bits == 24 ? TextureFormat::RGB : TextureFormat::RGBA);
		}

		uint result;
		glGenTextures(1, &result);
		glBindTexture(GL_TEXTURE_2D, result);

		if (byteAlignment) {
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TextureFilterToGL(m_Parameters.filter));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TextureFilterToGL(m_Parameters.filter));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TextureWrapToGL(m_Parameters.wrap));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TextureWrapToGL(m_Parameters.wrap));

		glTexImage2D(GL_TEXTURE_2D, 0, TextureFormatToGL(m_Parameters.format), m_Width, m_Height, 0, TextureFormatToGL(m_Parameters.format), GL_UNSIGNED_BYTE, pixels ? pixels : nullptr);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		if (pixels != nullptr) {
			delete[] pixels;
		}

		return result;
	}

	void Texture2D::SetData(byte* pixels, uint xoffset, uint yoffset, uint width, uint height) {
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
		glTexSubImage2D(GL_TEXTURE_2D, 0, xoffset, yoffset, width, height, TextureFormatToGL(m_Parameters.format), GL_UNSIGNED_BYTE, pixels);
	}

	void Texture2D::Bind(uint slot) const {
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
	}

	void Texture2D::Unbind(uint slot) const {
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}}