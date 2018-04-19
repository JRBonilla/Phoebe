#include "Font.h"

namespace ph { namespace renderer {

	Font::Font(const std::string& name, const std::string& filename, float size)
		: m_Name(name), m_Filename(filename), m_Size(size), m_Scale(math::Vec2(1.0f, 1.0f)) {
		if (FT_Init_FreeType(&m_FTLibrary)) {
			PH_INFO("Could not initialize FreeType library!");
		}
		if (FT_New_Face(m_FTLibrary, m_Filename.c_str(), 0, &m_FTFace)) {
			PH_INFO("Could not open font file " << m_Filename << "!");
		}

		m_FontAtlas = new FontAtlas(m_FTFace, m_Size);
		FT_Done_FreeType(m_FTLibrary);
	}

	Font::~Font() {
		delete m_FontAtlas;
	}

}}