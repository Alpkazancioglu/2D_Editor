#include "SaveHandler.h"

bool SAVEFILE::IsFileEmpty(const char* filename)
{
	std::ifstream file(filename);
	return file.peek() == std::ifstream::traits_type::eof();
}

void SAVEFILE::ReadSaveFile(const char* filename, GameObject& data)
{
	std::ifstream file(filename);


}

void SAVEFILE::WriteSaveFile(const char* filename, GameObject& data)
{

}
