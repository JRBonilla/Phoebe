#include "TextureAtlas.h"

namespace ph { namespace renderer {

	TextureAtlas::TextureAtlas(const std::string& filename, uint subImageWidth, uint subImageHeight)
		: m_Filename(filename), m_SubImageWidth(subImageWidth), m_SubImageHeight(subImageHeight) {
	}

	TextureAtlas::~TextureAtlas() {
	}

	uint TextureAtlas::Load() {
		return 0;
	}

}}