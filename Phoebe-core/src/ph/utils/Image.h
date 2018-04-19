#pragma once

#include <glad/glad.h>
#include <FreeImage.h>
#include <Utilities.h>
#include "Log.h"
#include "ph/Types.h"

namespace ph {

	class Image {
	private:
		static bool SwapRedBlue32(FIBITMAP* dib);
	public:
		static byte* Load(const char* filename, uint* width, uint* height, uint* bits, bool flipVertical);
		static byte* Load(const std::string& filename, uint* width, uint* height, uint* bits, bool flipVertical);
	private:
		Image() { }
	};

}