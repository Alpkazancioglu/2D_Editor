#pragma once
#include "Imgui/imgui.h"
#include "Imgui/imgui_internal.h"
#include "raylib.h"

namespace ImGui
{
	void SwitchBox(const char* str_id1,const char* str_id2,bool& active, bool Sameline = true);
	void ToggleButton(const char* str_id, bool* v);
	


}