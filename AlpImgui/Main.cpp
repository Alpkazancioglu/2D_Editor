#include <iostream>
#include "rlImGui.h"
#include "Imgui/imgui.h"
#include <string>
#include <memory>
#include <map>
#include "imguistyle.h"
#include <algorithm>
#include "GameObjects.h"



int main()
{



    const int screenWidth = 1200;
    const int screenHeight = 800;
   
       
    Enum_WarningStatus WarningLevel = Succeed;
    
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    std::map<std::string, GameObject> GameObjects;
    GameObject* SelectedObject;
    
    GameObjects["wood"] = GameObject("wood");
    GameObjects["wood"].Texture = LoadTexture(GetRelativePath("wood.png").c_str());
    GameObjects["wood"].Data.OriginalTextureSize = { (float)GameObjects["wood"].Texture.width,(float)GameObjects["wood"].Texture.height };
    GameObjects["wood"].RenderQueue = 0;
    
    SelectedObject = &GameObjects["wood"];
    
    Camera2D camera;
    camera.target = GetMousePosition();
    camera.offset = { (float)GetMonitorWidth(GetCurrentMonitor()) / 2,(float)GetMonitorHeight(GetCurrentMonitor()) / 2 };
    camera.zoom = 1.0f;
    camera.rotation = 0.0f;

    SetTargetFPS(60);
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    rlImGuiSetup(true);
    while (!WindowShouldClose())
    {

        BeginDrawing();
        
        
        ClearBackground(GRAY);
        rlImGuiBegin();
        
        Warning::WarningHandler(WarningLevel);
        
        
        SetPrioarity(GameObjects, SelectedObject);

        if (SelectedObject->ShouldObjectOrHitboxMove)
        {
            SelectObjectWithMouse(GameObjects, SelectedObject,camera.offset);
            SelectedObject->MoveObject(SelectedObject->MoveValue);
        
        }
        else
        {
            SelectHitboxWithMouse(SelectedObject);
            SelectedObject->MoveHitbox(SelectedObject->Hitbox.SelectedHitboxs, SelectedObject->MoveValue);
        }

        
        ImGui::GeneralMenu(GameObjects, SelectedObject, WarningLevel);
        ImGui::ObjectMenu(GameObjects, SelectedObject);
        BeginMode2D(camera);
        DrawObjects(GameObjects);
        DrawHitboxs(GameObjects, SelectedObject, false);
        
        camera.target.x += GetMouseDelta().x;
        camera.target.y += GetMouseDelta().y;

        camera.offset = { (float)GetMonitorWidth(GetCurrentMonitor()) / 2,(float)GetMonitorHeight(GetCurrentMonitor()) / 2 };
        std::cout << GetMousePosition().x << " :: " << GetMousePosition().y << std::endl;
        
        EndMode2D();

       

        rlImGuiEnd();
        
        EndDrawing();
        
    }

    rlImGuiShutdown();
    CloseWindow();

    return 0;
}




