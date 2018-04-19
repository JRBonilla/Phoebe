#include "Image.h"

namespace ph {

	byte* Image::Load(const char* filename, uint* width, uint* height, uint* bits, bool flipVertical) {
		FREE_IMAGE_FORMAT format = FreeImage_GetFileType(filename, 0);

		if (format == -1) {
			PH_ERROR("Could not load image file " << filename << "!");
		}

		if (format == FIF_UNKNOWN) {
			format = FreeImage_GetFIFFromFilename(filename);
		}

		if (format == FIF_UNKNOWN) {
			PH_ERROR("Could not determine image file format for " << filename << "!");
			return nullptr;
		}

		if (!FreeImage_FIFSupportsReading(format)) {
			PH_ERROR("Detected image format for " << filename << " could not be read!");
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

		if (flipVertical) {
			FreeImage_FlipVertical(bitmap32);
		}

		if (FreeImage_GetRedMask(bitmap32) == 0xff0000) {
			SwapRedBlue32(bitmap32);
		}

		int size = (*width) * (*height) * (bitsPerPixel / 8);
		byte* result = new byte[size];
		memcpy(result, pixels, size);
		FreeImage_Unload(bitmap32);
		return result;
	}

	byte* Image::Load(const std::string& filename, uint* width, uint* height, uint* bits, bool flipVertical) {
		return Load(filename.c_str(), width, height, bits, flipVertical);
	}
	
	bool Image::SwapRedBlue32(FIBITMAP* dib) {
		if (FreeImage_GetImageType(dib) != FIT_BITMAP) {
			return false;
		}

		const unsigned bytesPerPixel = FreeImage_GetBPP(dib) / 8;
		if (bytesPerPixel > 4 || bytesPerPixel < 3) {
			return false;
		}

		const unsigned height   = FreeImage_GetHeight(dib);
		const unsigned pitch    = FreeImage_GetPitch(dib);
		const unsigned lineSize = FreeImage_GetLine(dib);

		byte* line = FreeImage_GetBits(dib);
		for (unsigned y = 0; y < height; ++y, line += pitch) {
			for (byte* pixel = line; pixel < line + lineSize; pixel += bytesPerPixel) {
				INPLACESWAP(pixel[0], pixel[2]);
			}
		}

		return true;
	}

}