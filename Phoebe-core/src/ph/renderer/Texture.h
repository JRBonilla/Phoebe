#pragma once

#include <glad/glad.h>
#include "ph/Types.h"

namespace ph { namespace renderer {

	enum class TextureWrap {
		NONE = 0,
		REPEAT,
		MIRRORED_REPEAT,
		CLAMP_TO_EDGE,
		CLAMP_TO_BORDER
	};

	enum class TextureFilter {
		NONE = 0,
		LINEAR,
		NEAREST
	};

	enum class TextureFormat {
		NONE = 0,
		RED,
		ALPHA,
		RGB,
		RGBA
	};

	struct TextureParameters {
		TextureFilter  filter;
		TextureFormat  format;
		TextureWrap    wrap;

		TextureParameters() {
			format = TextureFormat::RGBA;
			filter = TextureFilter::NEAREST;
			wrap   = TextureWrap::CLAMP_TO_EDGE;
		}

		TextureParameters(TextureFormat format, TextureFilter filter, TextureWrap wrap)
			: format(format), filter(filter), wrap(wrap) {}

		TextureParameters(TextureFilter filter)
			: format(TextureFormat::RGBA), filter(filter), wrap(TextureWrap::CLAMP_TO_EDGE) {}

		TextureParameters(TextureFilter filter, TextureWrap wrap)
			: format(TextureFormat::RGBA), filter(filter), wrap(wrap) {}
	};

	struct TextureLoadOptions {
		bool flipHorizontal;
		bool flipVertical;

		TextureLoadOptions() {
			flipHorizontal = false;
			flipVertical = true;
		}

		TextureLoadOptions(bool flipHorizontal, bool flipVertical)
			: flipHorizontal(flipHorizontal), flipVertical(flipVertical) {}
	};

	class Texture {
	protected:
	public:
		virtual ~Texture() {}

		virtual void Bind(uint slot = 0) const = 0;
		virtual void Unbind(uint slot = 0) const = 0;
	protected:
		static uint const TextureFilterToGL(TextureFilter filter);
		static uint const TextureFormatToGL(TextureFormat format);
		static uint const TextureWrapToGL(TextureWrap wrap);
	};

}}