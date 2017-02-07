#include "Texture.h"

namespace ph { namespace graphics {

	Texture::Texture(const std::string& path, bool byteAlignment, TextureParameters parameters, TextureLoadOptions loadOptions)
		: m_FilePath(path), m_Parameters(parameters), m_LoadOptions(loadOptions) {
		m_TextureID = Load(byteAlignment);
	}

	Texture::Texture(uint width, uint height, bool byteAlignment, TextureParameters parameters, TextureLoadOptions loadOptions)
		: m_FilePath("NULL"), m_Width(width), m_Height(height), m_Parameters(parameters), m_LoadOptions(loadOptions) {
		m_TextureID = Load(byteAlignment);
	}

	Texture::~Texture() {
		glDeleteTextures(1, &m_TextureID);
	}

	GLuint Texture::Load(bool byteAlignment) {
		unsigned char* pixels = nullptr;

		if (m_FilePath != "NULL") {
			int bits = 0;
			pixels = Image::Load(m_FilePath.c_str(), &m_Width, &m_Height, &bits, !m_LoadOptions.FlipVertical);
			m_Parameters.format = (bits == 24 ? TextureFormat::RGB : TextureFormat::RGBA);
		}

		GLuint result;
		glGenTextures(1, &result);
		glBindTexture(GL_TEXTURE_2D, result);

		if (byteAlignment) {
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_Parameters.filter == TextureFilter::LINEAR ? GL_LINEAR : GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_Parameters.filter == TextureFilter::LINEAR ? GL_LINEAR : GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TextureWrapToGL(m_Parameters.wrap));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TextureWrapToGL(m_Parameters.wrap));

		glTexImage2D(GL_TEXTURE_2D, 0, TextureFormatToGL(m_Parameters.format), m_Width, m_Height, 0, TextureFormatToGL(m_Parameters.format), GL_UNSIGNED_BYTE, pixels ? pixels : nullptr);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		if (pixels != nullptr) {
			Image::Free(pixels);
		}

		return result;
	}

	void Texture::SetData(unsigned char* pixels, uint xoffset, uint yoffset, uint width, uint height) {
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
		glTexSubImage2D(GL_TEXTURE_2D, 0, xoffset, yoffset, width, height, TextureFormatToGL(m_Parameters.format), GL_UNSIGNED_BYTE, pixels);
	}


	void Texture::Bind(unsigned int slot) const {
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
	}

	void Texture::Unbind(unsigned int slot) const {
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	uint const Texture::TextureFormatToGL(TextureFormat format) {
		switch (format) {
		case TextureFormat::RED:	return GL_RED;
		case TextureFormat::ALPHA:	return GL_ALPHA;
		case TextureFormat::RGBA:	return GL_RGBA;
		case TextureFormat::RGB:	return GL_RGB;
		}
		return 0;
	}

	uint const Texture::TextureWrapToGL(TextureWrap wrap) {
		switch (wrap) {
		case TextureWrap::CLAMP_TO_BORDER:	return GL_CLAMP_TO_BORDER;
		case TextureWrap::CLAMP_TO_EDGE:	return GL_CLAMP_TO_EDGE;
		case TextureWrap::REPEAT:			return GL_REPEAT;
		case TextureWrap::MIRRORED_REPEAT:	return GL_MIRRORED_REPEAT;
		}
		return 0;
	}

}}