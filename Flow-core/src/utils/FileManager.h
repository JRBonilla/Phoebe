#pragma once

#include "Log.h"

namespace fl {
	
	class FileManager
	{
	private:
		FileManager() { }
	public:
		static std::string ReadFile(const char* filename);
		static std::string GetFileExtension(const std::string& filename);
	};

}