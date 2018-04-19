#include "TextureCube.h"

namespace ph { namespace renderer {

	TextureCube::TextureCube(const std::string& name, const std::string& filename) {
		m_Name = name;
		m_Files[0] = filename;
		m_TextureID = LoadFromFile();
	}

	TextureCube::TextureCube(const std::string& name, const std::string* files) {
		m_Name;
		m_Files = new std::string[6];
		for (uint i = 0; i < 6; i++) {
			m_Files[i] = files[i];
		}
		m_TextureID = LoadFromFiles();
	}

	TextureCube::TextureCube(const std::string& name, const std::string* files, uint mips, Layout layout) {
		m_Name;
		m_Files = new std::string[6];
		for (uint i = 0; i < 6; i++) {
			m_Files[i] = files[i];
		}
		if (layout == Layout::VERTICAL_CROSS) {
			m_TextureID = LoadFromVerticalCross(mips);
		}
		else if (layout == Layout::HORIZONTAL_CROSS) {
			m_TextureID = LoadFromHorizontalCross(mips);
		}
	}

	TextureCube::~TextureCube() {
		glDeleteTextures(1, &m_TextureID);
	}

	void TextureCube::Bind(uint slot) const {
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_TextureID);
	}

	void TextureCube::Unbind(uint slot) const {
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

	uint TextureCube::LoadFromFile() {
		return 0;
	}

	uint TextureCube::LoadFromFiles() {
		const std::string& xpos = m_Files[0];
		const std::string& xneg = m_Files[1];
		const std::string& ypos = m_Files[2];
		const std::string& yneg = m_Files[3];
		const std::string& zpos = m_Files[4];
		const std::string& zneg = m_Files[5];

		m_Parameters.format = TextureFormat::RGBA;

		uint width, height, bits;
		byte* xp = Image::Load(xpos, &width, &height, &bits, true);
		byte* xn = Image::Load(xneg, &width, &height, &bits, true);
		byte* yp = Image::Load(ypos, &width, &height, &bits, true);
		byte* yn = Image::Load(yneg, &width, &height, &bits, true);
		byte* zp = Image::Load(zpos, &width, &height, &bits, true);
		byte* zn = Image::Load(zneg, &width, &height, &bits, true);

		uint result;
		glGenTextures(1, &result);
		glBindTexture(GL_TEXTURE_CUBE_MAP, result);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		uint format = TextureFormatToGL(m_Parameters.format);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, xp);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, xn);
		delete xp, delete xn;

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, yp);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, yn);
		delete yp, delete yn;

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, zp);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, zn);
		delete zp, delete zn;
		
		glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

		m_Layout = Layout::HORIZONTAL_CROSS;

		return result;
	}

	uint TextureCube::LoadFromVerticalCross(uint mips) {
		return 0;
	}

	uint TextureCube::LoadFromHorizontalCross(uint mips) {
		return 0;
	}

}}