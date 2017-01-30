#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>
#include "Image.h"

namespace fl {

	unsigned char* Image::Load(const char* filename, int* width, int* height, int* bits, bool flipVertical) {
		stbi_set_flip_vertically_on_load(flipVertical);
		unsigned char* image = stbi_load(filename, width, height, bits, *bits);
		if (image == nullptr) {
			LOG("Could not load image " << filename << ": " << stbi_failure_reason());
			return nullptr;
		}
		return image;
	}

	void Image::Free(unsigned char* image) {
		stbi_image_free(image);
	}

}