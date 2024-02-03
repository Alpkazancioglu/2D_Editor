#include <iostream>
#include "rlImGui.h"
#include "Imgui/imgui.h"
#include <string>
#include <memory>
#include <map>
#include <unordered_map>
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
    GameObjects["wood"].Texture = LoadTexture(GetRelativePath("wood").c_str());
    GameObjects["wood"].Data.OriginalTextureSize = { (float)GameObjects["wood"].Texture.width,(float)GameObjects["wood"].Texture.height };
    GameObjects["wood"].RenderQueue = 0;
    
    SelectedObject = &GameObjects["wood"];
    
    

    SetTargetFPS(60);
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    rlImGuiSetup(true);
    while (!WindowShouldClose())
    {

        BeginDrawing();

        ClearBackground(GRAY);
        rlImGuiBegin();
        
        Warning::WarningHandler(WarningLevel);
        
        
       
        //std::cout << SelectedObject->RenderQueue << std::endl;
        SetPrioarity(GameObjects, SelectedObject);


        if (SelectedObject->ShouldObjectOrHitboxMove)
        {
            SelectObjectWithMouse(GameObjects, SelectedObject);
            SelectedObject->MoveObject(SelectedObject->MoveValue);
        
        }
        else
        {
            SelectHitboxWithMouse(SelectedObject, SelectedObject->Hitbox.HitboxFocus);
            SelectedObject->MoveHitbox(SelectedObject->MoveValue, SelectedObject->Hitbox.HitboxFocus);
        
        }


        ImGui::GeneralMenu(GameObjects, SelectedObject, WarningLevel);
        ImGui::ObjectMenu(GameObjects, SelectedObject);
        

        rlImGuiEnd();
        EndDrawing();

    }

    rlImGuiShutdown();
    CloseWindow();

    return 0;
}




