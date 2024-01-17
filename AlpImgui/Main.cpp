#include <iostream>
#include "rlImGui.h"
#include "Imgui/imgui.h"
#include <string>
#include "GameObjects.h"
#include <memory>

int main()
{
 
    
    
    const int screenWidth = 800;
    const int screenHeight = 450;
    enum Focus { Object,Hitboxs };
    std::string temp = "Object";
    std::string temp1 = "rec";
    int focus = 0;
    int HitboxFocus = 0;
    bool Checked = false;
    float IncreaseValue = 10.0f;
    GameObject wood;
    
    

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    
    wood.Texture = LoadTexture("C:\\Users\\user\\Desktop\\main()\\projects\\AlpImgui\\AlpImgui\\AlpImgui\\Wood.png");
    wood.Data.pos = { 200,200 };
    wood.Hitbox.Data.recs.resize(1);
    wood.Hitbox.Data.recs[0](Rectanglex(first,200 ,200,  wood.Texture.width, wood.Texture.height));
   
   
    
    
    


    SetTargetFPS(60);   
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    rlImGuiSetup(true); 	
    while (!WindowShouldClose())    
    {
       
        BeginDrawing();

        ClearBackground(GRAY);
        rlImGuiBegin();

        ImGui::SetNextWindowPos({ 0,0 });
        ImGui::Begin("Hello",(bool*)0 , ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove);
        ImGui::Text("AlpImgui1");
        ImGui::Separator();
        if(ImGui::BeginCombo("focus",temp.c_str()))
        {
            if(ImGui::Selectable("Object"))
            {
                temp = "Object";
            
                focus = Object;

            }
            else if(ImGui::Selectable("Hitboxs"))
            {
                temp = "Hitboxs";
                wood.ShouldHitboxDisplay = true;
                focus = Hitboxs;
            }
            ImGui::EndCombo();
        }
        
        ImGui::Checkbox("Show Hitbox", &wood.ShouldHitboxDisplay);
        ImGui::SameLine();
        if (ImGui::Button("Reset Hitbox")) wood.ResetHitbox();
        ImGui::SliderFloat("Increase Value", &IncreaseValue, 0.0f, 20.0f);
        
        if(ImGui::Button("Add Rec"))
        {
            wood.Hitbox.Data.recs.push_back(Rectanglex(numbers(wood.Hitbox.Data.recs.size()), 400, 200, wood.Texture.width, wood.Texture.height));
        }

        
        if(focus != Object)
        {
            
            if(ImGui::BeginMenu(temp1.c_str()))
            {
                for(int i = 0;i < wood.Hitbox.Data.recs.size();i++)
                {
                    if(ImGui::MenuItem(toString(wood.Hitbox.Data.recs[i].name)))
                    {
                        temp1 = toString(wood.Hitbox.Data.recs[i].name); 
                        wood.ShouldHitboxDisplay = true;
                        HitboxFocus = int(wood.Hitbox.Data.recs[i].name);
                        
                    }
                }
                
                
                
                ImGui::EndMenu();
            }
        }

        DrawTextureV(wood.Texture, wood.Data.pos, WHITE);
        if (wood.ShouldHitboxDisplay)
        {
            if(wood.Hitbox.ShowAllHitboxs)
            for(int i = 0; i < wood.Hitbox.Data.recs.size();i++)
            {
                DrawRectangleLinesEx(wood.Hitbox.Data.recs[i].ConvertRec(), 1.0f, WHITE);
            }
            else
            {
                
            }
        }
        
        std::cout << HitboxFocus << std::endl;
        switch (focus)
        {
        case Object: wood.MoveObject(IncreaseValue);
            break;
        case Hitboxs: 
            wood.MoveHitbox(IncreaseValue, numbers(HitboxFocus));
   
            break;
        }
       
        
        ImGui::End();
        rlImGuiEnd();

        EndDrawing();

        
    }

    UnloadTexture(wood.Texture);
    rlImGuiShutdown();
    CloseWindow();        
	return 0;
}




