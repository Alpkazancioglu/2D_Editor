#pragma once

#include "Imgui/imgui.h"
#include "raylib.h"


enum Enum_WarningStatus { Succeed, ObjectCreatingFailed, TextureFailed ,ObjectDeleted};


namespace Warning
{
	
	void WarningHandler(Enum_WarningStatus& WarningStatus);
	void TextureNotLoaded(Enum_WarningStatus& WarningStatus);
	void ObjectNotCreated(Enum_WarningStatus& WarningStatus);
	void ObjectDelete(Enum_WarningStatus& WarningStatus);
}


