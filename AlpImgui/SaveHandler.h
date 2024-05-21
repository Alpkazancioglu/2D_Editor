#pragma once
#include "GameObjects.h"
#include "json.hpp"
#include <fstream>


using json = nlohmann::json;

namespace SAVEFILE
{
	
	void handler(std::map<std::string, GameObject>& GameObjects, GameObject*& SelectedObject);
	bool IsFileEmpty(const char* filename);
	bool ReadSaveFile(const char* filename, std::map<std::string, GameObject>& GameObjects, GameObject* &selectedObject);
	bool WriteSaveFile(const char* filename, std::map<std::string, GameObject>& GameObjects);

}