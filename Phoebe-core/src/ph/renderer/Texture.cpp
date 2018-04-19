#include "Texture.h"

namespace ph { namespace renderer {

	uint const Texture::TextureFilterToGL(TextureFilter filter) {
		switch (filter) {
		case TextureFilter::LINEAR:   return GL_LINEAR;
		case TextureFilter::NEAREST:  return GL_NEAREST;
		case TextureFilter::NONE:     return GL_NONE;
		}
		return 0;
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