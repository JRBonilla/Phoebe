#include "Font.h"

namespace fl { namespace graphics {

	Font::Font(const std::string& name, const std::string& filename, float size)
		: m_Name(name), m_Filename(filename), m_Size(size), m_Scale(math::vec2(1, 1)) {
		if (FT_Init_FreeType(&m_FTLibrary)) {
			LOG("Could not initialize FreeType library!");
		}

		if (FT_New_Face(m_FTLibrary, m_Filename.c_str(), 0, &m_FTFace)) {
			LOG("Could not open font file " << m_Filename << "!");
		}

		m_FTAtlas = new FontTextureAtlas(m_FTFace, m_Size);
		FT_Done_FreeType(m_FTLibrary);
	}

	Font::~Font() {
		delete m_FTAtlas;
	}

}}