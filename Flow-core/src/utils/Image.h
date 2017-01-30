#pragma once

#include "Log.h"

namespace fl {

	class Image {
	private:
		Image() { }
	public:
		static unsigned char* Load(const char* filename, int* width, int* height, int* bits, bool flipVertical);
		static void Free(unsigned char* image);
	};

}