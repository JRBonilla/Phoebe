#include "FileManager.h"

namespace ph {
	
	// Returns the contents of a file
	std::string FileManager::ReadFile(const char* filename) {
		// Open the file
		FILE* file;
		file = fopen(filename, "rt");

		// Check that the file exists
		PHOENIX_ASSERT(file, "Could not open file " << filename << "!\n");

		// If it does, read it
		if (file != nullptr) {
			fseek(file, 0, SEEK_END);
			unsigned long length = ftell(file);
			char* data = new char[length + 1];
			memset(data, 0, length + 1);
			fseek(file, 0, SEEK_SET);
			fread(data, 1, length, file);
			fclose(file);

			std::string result(data);
			delete[] data;
			return result;
		}

		// Otherwise, return an empty string
		return std::string();
	}

	std::string FileManager::GetFileExtension(const std::string& filename) {
		return filename.substr(filename.find(".") + 1);
	}


}
