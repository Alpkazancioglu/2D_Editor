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
    enum Focus { Object, Hitboxs, allObjects };
    std::string Name_ObjectSelector = "Object";
    std::string temp1 = "rec";
    int focus = 0;
    Enum_WarningStatus WarningLevel = Succeed;
    numbers HitboxFocus = first;
    
    int IncreaseValue = 10.0f;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    std::map<std::string, GameObject> GameObjects;
    GameObject* SelectedObject;

    GameObjects["wood"] = GameObject("wood");
    GameObjects["wood"].Texture = LoadTexture(GetRelativePath("wood").c_str());
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
        
        
        ImGui::GeneralMenu(GameObjects, SelectedObject,WarningLevel);
        ImGui::ObjectMenu(GameObjects,SelectedObject);
        
        SetPrioarity(GameObjects, SelectedObject);
        SelectObjectWithMouse(GameObjects, SelectedObject);
        SelectHitboxWithMouse(SelectedObject, HitboxFocus);
  
        
        std::cout << SelectedObject->RenderQueue << std::endl;
        
        if (SelectedObject->ShouldObjectOrHitboxMove) SelectedObject->MoveObject(IncreaseValue);
        else SelectedObject->MoveHitbox(IncreaseValue,HitboxFocus);

        DrawObjects(GameObjects);
        DrawHitboxs(GameObjects, SelectedObject);
        

        rlImGuiEnd();
        EndDrawing();


    }

    rlImGuiShutdown();
    CloseWindow();

    return 0;
}




