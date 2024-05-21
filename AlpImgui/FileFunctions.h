#pragma once
#include <vector>
#include <string>
#include <raylib.h>
#include <filesystem>



namespace FilePath
{
	std::vector<std::pair<std::string, std::string>> ReadMultipleFilesFromDirectory(const char* FilePathToDirectory, const char* ext);
	std::string GetRelativeTexturePath(std::string TextureName);
	std::string GetRelativeTexturePath();
	std::string GetRelativePath(std::string extrapath);
	std::string  GetRelativePath();
}

