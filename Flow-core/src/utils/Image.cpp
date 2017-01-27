#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>
#include "Image.h"

namespace fl {

	unsigned char* Image::Load(const char* filename, int* width, int* height, int* bits, bool flipVertical) {
		stbi_set_flip_vertically_on_load(flipVertical);
		unsigned char* img = stbi_load(filename, width, height, bits, STBI_rgb_alpha);
		if (img == nullptr) {
			LOG("Could not load image " << filename << ": " << stbi_failure_reason());
			return nullptr;
		}
		int size = (*width) * (*height) * (*bits);
		unsigned char* result = new unsigned char[size];
		memcpy(result, img, size);
		stbi_image_free(img);
		return result;
	}

}