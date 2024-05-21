#include <iostream>
#include "rlImGui.h"
#include "Imgui/imgui.h"
#include <string>
#include <memory>
#include <map>
#include "imguistyle.h"
#include <algorithm>
#include "GameObjects.h"
#include "Camera.h"
#include "SaveHandler.h"
#include "WarningHandler.h"



int main()
{

	const int screenWidth = 1200;
	const int screenHeight = 800;
	
	
	Enum_WarningStatus WarningLevel = Succeed;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	std::map<std::string, GameObject> GameObjects;
	GameObject* SelectedObject;

	GameObjects["wood"] = GameObject("wood");
	GameObjects["wood"].Texture = LoadTexture(FilePath::GetRelativeTexturePath("wood.png").c_str());
	GameObjects["wood"].Data.OriginalTextureSize = { (float)GameObjects["wood"].Texture.width,(float)GameObjects["wood"].Texture.height };
	GameObjects["wood"].RenderQueue = 0;
	GameObjects["wood"].Data.TextureName = "wood.png";

	SelectedObject = &GameObjects["wood"];

	Camera2D camera = CAMERA::init();
	

	SetTargetFPS(60);
	SetWindowState(FLAG_WINDOW_RESIZABLE);

	rlImGuiSetup(true);
	while (!WindowShouldClose())
	{

		BeginDrawing();

		
		ClearBackground(GRAY);
		rlImGuiBegin();

		Warning::WarningHandler(WarningLevel,GameObjects,SelectedObject);


		SetPrioarity(GameObjects, SelectedObject);

		if (SelectedObject->Global.ShouldObjectOrHitboxMove)
		{
			SelectObjectWithMouse(GameObjects, SelectedObject,camera);
			SelectedObject->MoveObject(camera,SelectedObject->Global.MoveValue);

		}
		else
		{
			SelectHitboxWithMouse(SelectedObject,camera);
			SelectedObject->MoveHitbox(SelectedObject->Hitbox.SelectedHitboxs,camera,SelectedObject->Global.MoveValue);
		}

		


		ImGui::GeneralMenu(GameObjects, SelectedObject, WarningLevel);
		ImGui::ObjectMenu(GameObjects, SelectedObject);
		ImGui::CameraInfo(camera);
		MakeVariablesTheSame(GameObjects, SelectedObject); // arraydaki butun objelerde ayni olmasini istedigim degiskenleri burda esitliyorum
		//SAVEFILE::handler(GameObjects, SelectedObject);

		
		
		


		BeginMode2D(camera);
		
		DrawObjects(GameObjects);
		DrawHitboxs(GameObjects, SelectedObject,SelectedObject->Global.ShowAllHitboxs);

		
		CAMERA::moveCamera(camera);
		CAMERA::Zoom(camera);
	
		

		EndMode2D();
		rlImGuiEnd();
		EndDrawing();
	}

	rlImGuiShutdown();
	CloseWindow();

	return 0;
}




