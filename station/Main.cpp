#include <iostream>
#include "rlImGui.h"
#include "Imgui/imgui.h"
#include "Drone.h"
#include "rlgl.h"
#include "raymath.h"
#include "ImguiStyle.h"

int main()
{
	
	InitWindow(1200, 800, "station");
	SetTargetFPS(144);
	SetWindowState(FLAG_WINDOW_RESIZABLE);
	rlImGuiSetup(true);
	Texture2D background = LoadTexture(GetRelativeTexturePath("background.png").c_str());
	Texture2D building = LoadTexture(GetRelativeTexturePath("building.png").c_str());

	
	Drone drone;
	drone.data.droneStatus = DroneStatus::driving;
	drone.setTexture(drone.data.droneStatus);
	drone.data.pos = { 300,600 };
	drone.data.size = { 50,50 };
	drone.data.speed = { 0,0 };
	drone.data.rotation = 0;
	drone.data.batteryStatus = 100;

	while (!WindowShouldClose()) 
	{
		BeginDrawing();
		rlImGuiBegin();

		ClearBackground(GRAY);
		ImGui::InfoMenu(drone);

		
		DrawTexture(background, 0, 0, WHITE);
		DrawTexture(building, 1050, 520, WHITE);

		drone.transform();
		drone.Move();
		
		
		
		
		
		
		
		DrawTexturePro(drone.currentTexture, { 0,0,(float)drone.currentTexture.width,(float)drone.currentTexture.height }, {drone.data.pos.x,drone.data.pos.y,drone.data.size.width,drone.data.size.height }, { drone.data.size.width/2,drone.data.size.height /2}, drone.data.rotation, WHITE);
		
		
		print(drone.data.rotation);
		

		rlImGuiEnd();
		EndDrawing();


	}

	UnloadTexture(drone.textures.drivingTexture);
	UnloadTexture(drone.textures.flyingTexture);
	UnloadTexture(background);

	rlImGuiShutdown();
	
	return 0;
}




