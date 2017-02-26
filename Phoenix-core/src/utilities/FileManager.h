#pragma once

#include "Log.h"

namespace ph {
	
	class FileManager {
	public:
		static std::string ReadFile(const char* filename);
		static std::string ReadFile(const std::string& filename);
		static std::string GetFileExtension(const std::string& filename);
	private:
		FileManager() { }
	};

}