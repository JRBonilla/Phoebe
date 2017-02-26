#pragma once

#include <glad/glad.h>
#include <FreeImage.h>
#include <Utilities.h>
#include "../common/Types.h"
#include "Log.h"

namespace ph {

	class Image {
	public:
		static byte* Image::Load(const char* filename, int* width, int* height, uint* bits, bool FlipVertical);
	private:
		static bool SwapRedBlue32(FIBITMAP* dib);
	private:
		Image() { }
	};

}