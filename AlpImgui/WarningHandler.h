#pragma once

#include "Imgui/imgui.h"
#include "raylib.h"
#include "FileFunctions.h"
#include "SaveHandler.h"





namespace Warning
{
	
	void WarningHandler(Enum_WarningStatus& WarningStatus, std::map<std::string, GameObject>& GameObjects, GameObject*& selectedObject);
	void TextureNotLoaded(Enum_WarningStatus& WarningStatus);
	void ObjectNotCreated(Enum_WarningStatus& WarningStatus);
	void ObjectDelete(Enum_WarningStatus& WarningStatus);
	void FileSave(Enum_WarningStatus& WarningStatus);
	void FileLoad(Enum_WarningStatus& WarningStatus);
	void FileSelector(Enum_WarningStatus& WarningStatus, std::map<std::string, GameObject>& GameObjects, GameObject*& selectedObject);

}


