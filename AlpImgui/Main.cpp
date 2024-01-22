#include <iostream>
#include "rlImGui.h"
#include "Imgui/imgui.h"
#include <string>
#include "GameObjects.h"
#include <memory>
#include <map>
#include <unordered_map>
#include "imguistyle.h"




int main()
{



    const int screenWidth = 800;
    const int screenHeight = 450;
    enum Focus { Object, Hitboxs, allObjects };
    std::string temp = "Object";
    std::string temp1 = "rec";
    int focus = 0;
    int HitboxFocus = 0;
    Enum_WarningStatus WarningStatus = Succeed;
    bool Checked = false;
    bool ShouldObjectCreated = false;
    bool ShouldObjectOrHitboxMove = true;
    int IncreaseValue = 10.0f;




    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    GameObject wood;


    wood.Texture = LoadTexture(GetRelativePath("wood").c_str());
    wood.Data.pos = { 200,200 };
    wood.Hitbox.recs.resize(1);
    wood.Hitbox.recs[0](Rectanglex(first, 200, 200, wood.Texture.width, wood.Texture.height));

    std::unordered_map<std::string, GameObject> GameObjects;

    GameObjects["wood"] = GameObject("wood");
    GameObjects["wood"].Texture = wood.Texture;
    GameObjects["wood"].Hitbox.recs.push_back(Rectanglex(first, 200, 200, wood.Texture.width, wood.Texture.height));
    
    GameObject* SelectedObject = new GameObject;
    

    
    
    SelectedObject = &GameObjects["wood"];
    
    
    //GameObjects["killua"].Hitbox.recs.push_back(Rectanglex(first,200,200,200,200));
    

    
    


    SetTargetFPS(60);   
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    rlImGuiSetup(true); 	
    while (!WindowShouldClose())    
    {
       
        BeginDrawing();

        ClearBackground(GRAY);
        rlImGuiBegin();
        

        ImGui::SetNextWindowPos({ 0,0 });
        if (ImGui::Begin("Hello", (bool*)0, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize))
        {

            ImGui::Text("AlpImgui1");
            ImGui::Separator();
            if (ImGui::BeginCombo("focus", temp.c_str()))
            {
                for(auto& object : GameObjects)
                {
                    if(ImGui::Selectable(object.second.ObjectName.c_str()))
                    {
                        temp = object.second.ObjectName;
                        SelectedObject = &object.second;
                    }
                }
                ImGui::EndCombo();
            }
           
            Warning::WarningHandler(WarningStatus);
                       
            if ((ImGui::Button("Add Objects") || ShouldObjectCreated))
            {
               WarningStatus = CreateNewObject(ShouldObjectCreated, GameObjects);
            }
            
             
        }ImGui::End();
        
       
            
        

         

        
        

        //ImGui::ShowDemoWindow();

        ImGui::SetWindowPos({ 1000,0});
        if(ImGui::Begin("alpino", (bool*)0 , ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImGui::Checkbox("Show Hitbox",&SelectedObject->ShouldHitboxDisplay);
            ImGui::SameLine();
            if (ImGui::Button("Reset Hitbox")) SelectedObject->ResetHitbox();
            ImGui::SameLine();
            
            
            ImGui::SwitchBox("Object", "Hitbox", ShouldObjectOrHitboxMove);
            
            
           
            ImGui::SliderInt("Increase Value", &IncreaseValue, 1.0, 20.0);

            if (ImGui::Button("Add Rec"))
            {
                SelectedObject->Hitbox.recs.push_back(Rectanglex(numbers(SelectedObject->Hitbox.recs.size()), 400, 200, SelectedObject->Texture.width, SelectedObject->Texture.height));
            }
           
            if (ImGui::BeginMenu(temp1.c_str()))
            {
                for (int i = 0; i < SelectedObject->Hitbox.recs.size(); i++)
                {
                    if (ImGui::MenuItem(toString(SelectedObject->Hitbox.recs[i].name)))
                    {
                        temp1 = toString(SelectedObject->Hitbox.recs[i].name);
                        //wood.ShouldHitboxDisplay = true;
                        HitboxFocus = int(SelectedObject->Hitbox.recs[i].name);

                    }
                }

                ImGui::EndMenu();
            }
            
        }ImGui::End();
        
        if (ShouldObjectOrHitboxMove) SelectedObject->MoveObject(IncreaseValue);
        else SelectedObject->MoveHitbox(IncreaseValue, (numbers)HitboxFocus);

        
        DrawTextureV(SelectedObject->Texture, SelectedObject->Data.pos, WHITE);
        if (SelectedObject->ShouldHitboxDisplay)
        {
            for (int i = 0; i < SelectedObject->Hitbox.recs.size(); i++)
            {
                DrawRectangleLinesEx(SelectedObject->Hitbox.recs[i].ConvertRec(), 1.0f, WHITE);
            }
        }
                
           

        //std::cout << GameObjects["killua"].Hitbox.recs[0].height << std::endl;
        
        
        
        rlImGuiEnd();
        EndDrawing();

        
    }
    
    rlImGuiShutdown();
    CloseWindow();        
    
    return 0;
}




