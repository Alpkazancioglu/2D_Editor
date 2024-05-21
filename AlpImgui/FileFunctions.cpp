#include "FileFunctions.h"


std::vector<std::pair<std::string, std::string>> FilePath::ReadMultipleFilesFromDirectory(const char* FilePathToDirectory, const char* ext)
{

	std::vector<std::pair<std::string, std::string>> result;
	std::string path = FilePathToDirectory;
	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		std::string PathDirect = entry.path().generic_string().c_str();
		if (IsFileExtension(PathDirect.c_str(), ext))
		{
			std::string PathName;
			if (PathDirect.find('/') != std::string::npos)
			{
				PathName = strrchr(PathDirect.c_str(), '/') + 1;
			}
			else if (PathDirect.find('\\') != std::string::npos)
			{
				PathName = strrchr(PathDirect.c_str(), '\\') + 1;
			}
			result.push_back({ PathName,entry.path().generic_string().c_str() });
		}

	}

	return result;

}

std::string FilePath::GetRelativeTexturePath(std::string TextureName)
{
	std::string WorkingDir(GetWorkingDirectory());

	for (size_t i = 0; i < WorkingDir.size(); i++)
	{
		if (WorkingDir.at(i) == '\\') {
			WorkingDir.at(i) = '/';
		}
	}
	std::string TexturePath(WorkingDir + "/Textures/" + TextureName);
	return TexturePath;
}

std::string FilePath::GetRelativeTexturePath()
{
	std::string WorkingDir(GetWorkingDirectory());

	for (size_t i = 0; i < WorkingDir.size(); i++)
	{
		if (WorkingDir.at(i) == '\\') {
			WorkingDir.at(i) = '/';
		}
	}
	std::string TexturePath(WorkingDir + "/Textures/");
	return TexturePath;
}

std::string FilePath::GetRelativePath()
{
	std::string WorkingDir(GetWorkingDirectory());

	for (size_t i = 0; i < WorkingDir.size(); i++)
	{
		if (WorkingDir.at(i) == '\\') {
			WorkingDir.at(i) = '/';
		}
	}
	std::string TexturePath(WorkingDir);
	return TexturePath;
}

std::string FilePath::GetRelativePath(std::string extrapath)
{
	std::string WorkingDir(GetWorkingDirectory());

	for (size_t i = 0; i < WorkingDir.size(); i++)
	{
		if (WorkingDir.at(i) == '\\') {
			WorkingDir.at(i) = '/';
		}
	}
	std::string TexturePath(WorkingDir);
	return TexturePath + extrapath;
}