#pragma once

#include <string>
#include <glad/glad.h>
#include "../utils/Image.h"
#include "../Types.h"

namespace fl { namespace graphics {

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

	struct TextureParameters
	{
		TextureFilter filter;
		TextureFormat format;
		TextureWrap wrap;

		TextureParameters()
		{
			format = TextureFormat::RGBA;
			filter = TextureFilter::NEAREST;
			wrap = TextureWrap::CLAMP_TO_EDGE;
		}

		TextureParameters(TextureFormat format, TextureFilter filter, TextureWrap wrap)
			: format(format), filter(filter), wrap(wrap)
		{
		}

		TextureParameters(TextureFilter filter)
			: format(TextureFormat::RGBA), filter(filter), wrap(TextureWrap::CLAMP_TO_EDGE)
		{
		}

		TextureParameters(TextureFilter filter, TextureWrap wrap)
			: format(TextureFormat::RGBA), filter(filter), wrap(wrap)
		{
		}
	};

	struct TextureLoadOptions
	{
		bool FlipHorizontal;
		bool FlipVertical;

		TextureLoadOptions()
		{
			FlipHorizontal = false;
			FlipVertical = false;
		}

		TextureLoadOptions(bool flipHorizontal, bool flipVertical)
			: FlipHorizontal(flipHorizontal), FlipVertical(flipVertical)
		{
		}
	};

	class Texture
	{
	private:
		std::string m_FilePath;
		GLuint m_TextureID;
		GLsizei m_Width, m_Height;
		TextureParameters m_Parameters;
		TextureLoadOptions m_LoadOptions;
	public:
		Texture(const std::string& path, bool UnpackAsByte = false, TextureParameters parameters = TextureParameters(), TextureLoadOptions loadOptions = TextureLoadOptions());
		Texture(uint width, uint height, bool UnpackAsByte = false, TextureParameters parameters = TextureParameters(), TextureLoadOptions loadOptions = TextureLoadOptions());
		~Texture();

		void SetData(unsigned char* pixels, uint xoffset, uint yoffset, uint width, uint height);

		void Bind(unsigned int slot) const;
		void Unbind(unsigned int slot) const;

		inline const GLuint getID() const { return m_TextureID; }
		inline GLsizei getWidth() const { return m_Width; }
		inline GLsizei getHeight() const { return m_Height; }
	private:
		GLuint load(bool UnpackAsByte = false);
		static uint const TextureFormatToGL(TextureFormat format);
		static uint const TextureWrapToGL(TextureWrap wrap);
	};

}}