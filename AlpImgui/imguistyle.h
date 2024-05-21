#pragma once
#include "Imgui/imgui.h"
#include "Imgui/imgui_internal.h"
#include "raylib.h"
#include "GameObjects.h"
#include <map>
#include <string>
#include "WarningHandler.h"
#include "SaveHandler.h"



namespace ImGui
{
	
	
	void SwitchBox(const char* str_id1,const char* str_id2,bool& active, bool sameline = true);
	void TextureMenu(std::map<std::string,GameObject> &objects , GameObject* &SelectedObject);
	void GeneralMenu(std::map<std::string, GameObject>& objects, GameObject*& SelectedObject, Enum_WarningStatus &WarningLevel);
	void HitboxMenu(std::map<std::string, GameObject>& objects, GameObject*& SelectedObject);
	void ObjectMenu(std::map<std::string, GameObject>& objects, GameObject*& SelectedObject);
	void TextureInfo(GameObject*& SelectedObject);
	void HitboxInfo(GameObject*& SelectedObject);
	void CameraInfo(Camera2D camera);



}