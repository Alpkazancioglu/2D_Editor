#include <iostream>
#include "rlImGui.h"
#include "Imgui/imgui.h"
#include <string>
#include "GameObjects.h"
#include <memory>
#include <map>
#include <unordered_map>
#include "imguistyle.h"
#include <algorithm>


int main()
{



    const int screenWidth = 1200;
    const int screenHeight = 800;
    enum Focus { Object, Hitboxs, allObjects };
    std::string temp = "Object";
    std::string temp1 = "rec";
    int focus = 0;
    numbers HitboxFocus = first;
    Enum_WarningStatus WarningStatus = Succeed;
    bool Checked = false;
    bool ShouldObjectCreated = false;
    bool ShouldObjectOrHitboxMove = true;
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


        ImGui::SetNextWindowPos({ 0,0 });
        if (ImGui::Begin("Hello", (bool*)0, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize))
        {

            ImGui::Text("AlpImgui1");
            ImGui::Separator();
            if (ImGui::BeginCombo("focus", temp.c_str()))
            {
                for (auto& object : GameObjects)
                {
                    if (ImGui::Selectable(object.second.ObjectName.c_str()))
                    {
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

        SelectObjectWithMouse(GameObjects, SelectedObject);
        SetPrioarity(GameObjects, SelectedObject);
        temp = SelectedObject->ObjectName;



        static ImVec2 alpinowindowsize = {};
        ImGui::SetNextWindowPos({ GetScreenWidth() - alpinowindowsize.x,0 });
        if (ImGui::Begin("alpino", (bool*)0, ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImGui::Checkbox("Show Hitbox", &SelectedObject->ShouldHitboxDisplay);
            ImGui::SameLine();
            if (ImGui::Button("Reset Hitbox")) SelectedObject->ResetHitbox();
            ImGui::SameLine();
            ImGui::SwitchBox("Object", "Hitbox", ShouldObjectOrHitboxMove);
            ImGui::SliderFloat("Increase Value", &SelectedObject->Data.TextureScale, 0.0f, 20.0f);

            if (ImGui::Button("Add Rec"))
            {
                SelectedObject->Hitbox.recs.push_back(Rectanglex(numbers(SelectedObject->Hitbox.recs.size()), 400, 200, SelectedObject->Texture.width, SelectedObject->Texture.height));
            }



            if (!SelectedObject->Hitbox.recs.empty() && ImGui::BeginMenu("Rec"))
            {
                for (int i = 0; i < SelectedObject->Hitbox.recs.size(); i++)
                {
                    if (ImGui::MenuItem(toString(SelectedObject->Hitbox.recs[i].name)))
                    {
                        HitboxFocus = SelectedObject->Hitbox.recs[i].name;
                    }
                }

                ImGui::EndMenu();
            }

            alpinowindowsize = ImGui::GetWindowSize();
            ImGui::End();
        }

        SelectHitboxWithMouse(SelectedObject, HitboxFocus);
        

        if (ShouldObjectOrHitboxMove) SelectedObject->MoveObject(IncreaseValue);
        else SelectedObject->MoveHitbox(IncreaseValue, HitboxFocus);

        

        //DrawTextureV(SelectedObject->Texture, SelectedObject->Data.pos, WHITE);
        std::cout << SelectedObject->RenderQueue << std::endl;
        DrawObjects(GameObjects);
        DrawHitboxs(GameObjects, SelectedObject);
        //DrawTextureEx(SelectedObject->Texture, SelectedObject->Data.pos, SelectedObject->Data.rotation, SelectedObject->Data.TextureScale, WHITE);
       


        rlImGuiEnd();
        EndDrawing();


    }

    rlImGuiShutdown();
    CloseWindow();

    return 0;
}




