#pragma once

#include "Imgui/imgui.h"
#include "raylib.h"

enum Enum_WarningStatus { Succeed ,ObjectFailed,TextureFailed};



namespace Warning
{
	void WarningHandler(Enum_WarningStatus& WarningStatus);
	void TextureNotLoaded(Enum_WarningStatus& WarningStatus);
	void ObjectNotLoaded(Enum_WarningStatus& WarningStatus);
}


