#pragma once
#include "GameObjects.h"
#include "json.hpp"
#include <fstream>


using json = nlohmann::json;

namespace SAVEFILE
{
	
	
	bool IsFileEmpty(const char* filename);
	void ReadSaveFile(const char* filename,GameObject& data);
	void WriteSaveFile(const char* filename, GameObject& data);

	








}