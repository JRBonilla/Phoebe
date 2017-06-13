#include "Image.h"

namespace ph {

	byte* Image::Load(const char* filename, int* width, int* height, uint* bits, bool FlipVertical) {
		FREE_IMAGE_FORMAT format = FreeImage_GetFileType(filename, 0);

		if (format == -1) {
			PHOENIX_INFO("Could not load image file " << filename << "!");
		}

		if (format == FIF_UNKNOWN) {
			format = FreeImage_GetFIFFromFilename(filename);
		}

		if (format == FIF_UNKNOWN) {
			PHOENIX_INFO("Could not determine image file format for " << filename << "!");
			return nullptr;
		}

		if (!FreeImage_FIFSupportsReading(format)) {
			PHOENIX_INFO("Detected image format for " << filename << " could not be read!");
			return nullptr;
		}

		FIBITMAP* bitmap = FreeImage_Load(format, filename);

		int bitsPerPixel = FreeImage_GetBPP(bitmap);

		FIBITMAP* bitmap32;
		if (bitsPerPixel == 32) {
			bitmap32 = bitmap;
		}
		else {
			bitmap32 = FreeImage_ConvertTo32Bits(bitmap);
			bitsPerPixel = FreeImage_GetBPP(bitmap32);
			FreeImage_Unload(bitmap);
		}

		byte* pixels = FreeImage_GetBits(bitmap32);

		*width = FreeImage_GetWidth(bitmap32);
		*height = FreeImage_GetHeight(bitmap32);
		*bits = bitsPerPixel;

		if (FlipVertical) {
			FreeImage_FlipVertical(bitmap32);
		}

		if (FreeImage_GetRedMask(bitmap) == 0xff0000) {
			SwapRedBlue32(bitmap32);
		}

		int size = (*width) * (*height) * (bitsPerPixel / 8);
		byte* result = new byte[size];
		memcpy(result, pixels, size);
		FreeImage_Unload(bitmap32);
		return result;
	}
	
	bool Image::SwapRedBlue32(FIBITMAP* dib) {
		if (FreeImage_GetImageType(dib) != FIT_BITMAP) {
			return false;
		}

		const unsigned bytesperpixel = FreeImage_GetBPP(dib) / 8;
		if (bytesperpixel > 4 || bytesperpixel < 3) {
			return false;
		}

		const unsigned height = FreeImage_GetHeight(dib);
		const unsigned pitch = FreeImage_GetPitch(dib);
		const unsigned lineSize = FreeImage_GetLine(dib);

		BYTE* line = FreeImage_GetBits(dib);
		for (unsigned y = 0; y < height; ++y, line += pitch) {
			for (BYTE* pixel = line; pixel < line + lineSize; pixel += bytesperpixel) {
				INPLACESWAP(pixel[0], pixel[2]);
			}
		}

		return true;
	}

}