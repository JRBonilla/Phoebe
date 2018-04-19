#pragma once

#include <vector>
#include "Log.h"
#include "ph/Types.h"

namespace ph {
	
	class FileManager {
	public:
		static std::string ReadFile(const char* filename);
		static std::string ReadFile(const std::string& filename);

		static std::string GetDirectory(const std::string& path);
		static std::string GetFileExtension(const std::string& filename);
		static std::string GetBlock(const std::vector<std::string>& lines, const char* begin, uint index);

		static std::vector<std::string> SplitString(const std::string& string, const char delimiter);
		static std::vector<std::string> SplitString(const std::string& string, const std::string& delimiters);
		static std::vector<std::string> GetLines(const std::string& string);

		static byte* ReadBytes(FILE* file, byte* buffer, uint size);
		static void  WriteBytes(FILE* file, const byte* data, uint size);
	private:
		FileManager() { }
	};

}