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
    enum Focus { Object, Hitboxs,allObjects};
    std::string temp = "Object";
    std::string temp1 = "rec";
    int focus = 0;
    int HitboxFocus = 0;
    bool Checked = false;
    bool ShouldObjectCreated = false;
 
    int IncreaseValue = 10.0f;
    
 
    

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    GameObject wood;
    

    wood.Texture = LoadTexture("C:\\Users\\user\\Desktop\\main()\\projects\\AlpImgui\\AlpImgui\\AlpImgui\\Textures\\Wood.png");
    wood.Data.pos = { 200,200 };
    wood.Hitbox.recs.resize(1);
    wood.Hitbox.recs[0](Rectanglex(first,200 ,200,  wood.Texture.width, wood.Texture.height));
   
    std::unordered_map<std::string, GameObject> GameObjects;
   
    char alp[5] = {};

    GameObjects["wood"] = GameObject("wood");
    
    GameObjects["killua"] = GameObject("killua");
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
                        
                    }
                }
                ImGui::EndCombo();
            }
            
            if (ImGui::Button("Add Objects") || ShouldObjectCreated)
            {
                CreateNewObject(ShouldObjectCreated, GameObjects);
            }
             
           //for(auto& objects : GameObjects)
            //std::cout << GetWorkingDirectory() << std::endl;
            


        }ImGui::End();
        
       

        ImGui::SetWindowPos({ 1000,0});
        if(ImGui::Begin("alpino", (bool*)0 , ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImGui::Checkbox("Show Hitbox", &wood.ShouldHitboxDisplay);
            ImGui::SameLine();
            if (ImGui::Button("Reset Hitbox")) wood.ResetHitbox();
            ImGui::SameLine();
            
            static bool ShouldObjectOrHitboxMove = true;
            ImGui::SwitchBox("Object", "Hitbox", ShouldObjectOrHitboxMove);
            
            std::cout << (float)GetScreenWidth() << std::endl;
            
            ImGui::SliderInt("Increase Value", &IncreaseValue, 1.0, 20.0);

            if (ImGui::Button("Add Rec"))
            {
                wood.Hitbox.recs.push_back(Rectanglex(numbers(wood.Hitbox.recs.size()), 400, 200, wood.Texture.width, wood.Texture.height));
            }
            if (focus != Object)
            {

                if (ImGui::BeginMenu(temp1.c_str()))
                {
                    for (int i = 0; i < wood.Hitbox.recs.size(); i++)
                    {
                        if (ImGui::MenuItem(toString(wood.Hitbox.recs[i].name)))
                        {
                            temp1 = toString(wood.Hitbox.recs[i].name);
                            wood.ShouldHitboxDisplay = true;
                            HitboxFocus = int(wood.Hitbox.recs[i].name);

                        }
                    }

                    ImGui::EndMenu();
                }
            }
        }ImGui::End();

        DrawTextureV(wood.Texture, wood.Data.pos, WHITE);
        if (wood.ShouldHitboxDisplay)
        {
            if (wood.Hitbox.ShowAllHitboxs)
                for (int i = 0; i < wood.Hitbox.recs.size(); i++)
                {
                    DrawRectangleLinesEx(wood.Hitbox.recs[i].ConvertRec(), 1.0f, WHITE);
                }
            else
            {

            }
        }

        //std::cout << GameObjects["killua"].Hitbox.recs[0].height << std::endl;
        switch (focus)
        {
        case Object: wood.MoveObject(IncreaseValue);
            break;
        case Hitboxs:
            wood.MoveHitbox(IncreaseValue, numbers(HitboxFocus));
            break;
        }

        
        rlImGuiEnd();
        EndDrawing();

        
    }

    rlImGuiShutdown();
    CloseWindow();        
	return 0;
}




