#include "imguistyle.h"






void ImGui::SwitchBox(const char* str_id1,const char* str_id2,bool &active  ,bool Sameline)
{
    
    static bool temp = !active;
    
    

    ImGui::Checkbox(str_id1, &active);
    if (active) temp = false;
    if (SameLine) ImGui::SameLine();
    ImGui::Checkbox(str_id2, &temp);
    if (temp) active = false;
    
    
    

}



void ImGui::ObjectMenu(std::map<std::string, GameObject> &objects, GameObject* &SelectedObject)
{
    static ImVec2 alpinowindowsize = {};
    
    
    ImGui::SetNextWindowPos({ GetScreenWidth() - alpinowindowsize.x,0 });
    if (ImGui::Begin("alpino", (bool*)0, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Checkbox("Show Hitbox", &SelectedObject->ShouldHitboxDisplay);
        ImGui::SameLine();
        if (ImGui::Button("Reset Hitbox")) SelectedObject->ResetHitbox();
        ImGui::SameLine();
        ImGui::SwitchBox("Object", "Hitbox", SelectedObject->ShouldObjectOrHitboxMove);
        ImGui::SliderFloat("Increase Value", &SelectedObject->Data.TextureScale, 0.0f, 20.0f);

        if (ImGui::Button("Add Rec"))
        {
            SelectedObject->Hitbox.recs.push_back(Rectanglex(numbers(SelectedObject->Hitbox.recs.size()), 400, 200, SelectedObject->Texture.width, SelectedObject->Texture.height));
        }

        static std::string name_RecSelector = "rec";
        if (!SelectedObject->Hitbox.recs.empty() && ImGui::BeginMenu(name_RecSelector.c_str()))
        {
            for (int i = 0; i < SelectedObject->Hitbox.recs.size(); i++)
            {
                if (ImGui::MenuItem(toString(SelectedObject->Hitbox.recs[i].name)))
                {
                    name_RecSelector = toString(SelectedObject->Hitbox.recs[i].name);
                }
            }
            ImGui::EndMenu();
        }

        for(auto& object : objects)
        {
            object.second.ShouldObjectOrHitboxMove = SelectedObject->ShouldObjectOrHitboxMove;
        }

        alpinowindowsize = ImGui::GetWindowSize();
        ImGui::End();
    }
}

void ImGui::GeneralMenu(std::map<std::string, GameObject>& GameObjects, GameObject*& SelectedObject ,Enum_WarningStatus &WarningLevel)
{
    ImGui::SetNextWindowPos({ 0,0 });
    if (ImGui::Begin("Hello", (bool*)0, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize))
    {

        ImGui::Text("AlpImgui1");
        ImGui::Separator();
        if (ImGui::BeginCombo("Selected Object", SelectedObject->ObjectName.c_str()))
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
        static bool ShouldObjectCreated = false;
        if ((ImGui::Button("Add Objects") || ShouldObjectCreated))
        {
            WarningLevel = CreateNewObject(ShouldObjectCreated, GameObjects);
        }


    }ImGui::End();
}



