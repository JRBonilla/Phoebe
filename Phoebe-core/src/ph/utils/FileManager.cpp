#include "FileManager.h"

namespace ph {
	
	// Returns the contents of a file
	std::string FileManager::ReadFile(const char* filename) {
		// Open the file
		FILE* file;
		file = fopen(filename, "rt");

		// Check that the file exists
		PH_ASSERT(file, "Could not open file " << filename << "!\n");

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

	std::string FileManager::ReadFile(const std::string& filename) {
		return ReadFile(filename.c_str());
	}

	std::vector<std::string> FileManager::SplitString(const std::string& string, const char delimiter) {
		size_t start = 0;
		size_t end = string.find_first_of(delimiter);

		std::vector<std::string> result;

		while (end <= std::string::npos) {
			result.emplace_back(string.substr(start, end - start));

			if (end == std::string::npos) {
				break;
			}

			start = end + 1;
			end = string.find_first_of(delimiter, start);
		}

		return result;
	}

	std::vector<std::string> FileManager::SplitString(const std::string& string, const std::string& delimiters) {
		size_t start = 0;
		size_t end = string.find_first_of(delimiters);

		std::vector<std::string> result;

		while (end <= std::string::npos) {
			result.emplace_back(string.substr(start, end - start));

			if (end == std::string::npos) {
				break;
			}

			start = end + 1;
			end = string.find_first_of(delimiters, start);
		}

		return result;
	}

	std::vector<std::string> FileManager::GetLines(const std::string& string) {
		return SplitString(string, '\n');
	}

	std::string FileManager::GetDirectory(const std::string& path) {
		std::vector<std::string> pathTokens = SplitString(path, "/\\");
		return path.substr(0, path.find(pathTokens.back()));
	}

	std::string FileManager::GetFileExtension(const std::string& filename) {
		return filename.substr(filename.find(".") + 1);
	}

	std::string FileManager::GetBlock(const std::vector<std::string>& lines, const char* begin, uint index) {
		std::string block = begin;
		if (const char* newLine = strstr(begin, "\n")) {
			block = std::string(block.c_str(), newLine - block.c_str());
		}

		uint nextIndex = index + 1;
		std::string nextLine = lines[nextIndex];
		while (!strstr(nextLine.c_str(), "};")) {
			if (nextLine == "\n" || nextLine == "") {
				nextIndex++;
				nextLine = lines[nextIndex];
				continue;
			}
			if (const char* newLine = strstr(nextLine.c_str(), "\n")) {
				nextLine = std::string(nextLine.c_str(), newLine - nextLine.c_str());
			}
			if (nextLine.front() == '\t') {
				nextLine = nextLine.substr(1);
			}
			block += " " + nextLine;
			nextIndex++;
			nextLine = lines[nextIndex];
		}
		block += " };";
		return block;
	}

	void FileManager::WriteBytes(FILE* file, const byte* data, uint size) {
		fwrite(data, 1, size, file);
	}

	byte* FileManager::ReadBytes(FILE* file, byte* buffer, uint size) {
		fread(buffer, 1, size, file);
		return buffer;
	}

}
