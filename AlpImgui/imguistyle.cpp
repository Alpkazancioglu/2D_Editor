#include "imguistyle.h"






void ImGui::SwitchBox(const char* str_id1,const char* str_id2,bool &active  ,bool sameline)
{
     
    static bool temp = !active;   
    ImGui::Checkbox(str_id1, &active);
    if (active) temp = false;
    if (sameline) ImGui::SameLine();
    ImGui::Checkbox(str_id2, &temp);
    if (temp) active = false;
  
}



void ImGui::TextureMenu(std::map<std::string, GameObject>& objects, GameObject*& SelectedObject)
{
   
    ImGui::Spacing();
    ImGui::Text("IncreaseValue = %d",SelectedObject->MoveValue);
    ImGui::SameLine();
    if (ImGui::ArrowButton("IncreaseLeft", ImGuiDir_Left) && SelectedObject->MoveValue != 1) { SelectedObject->MoveValue--; }
    ImGui::SameLine();
    if (ImGui::ArrowButton("IncreaseRight", ImGuiDir_Right) && SelectedObject->MoveValue != 5) { SelectedObject->MoveValue++; }
    ImGui::Separator();    
    ImGui::TextureInfo(SelectedObject);
    ImGui::Text("RenderQueue = %d", SelectedObject->RenderQueue);
    ImGui::SameLine();
    if (ImGui::ArrowButton("RenderLeft", ImGuiDir_Left))
    {
        IncreaseRenderQueue(objects,SelectedObject);
    }
    ImGui::SameLine();
    if (ImGui::ArrowButton("RenderRight", ImGuiDir_Right))
    {
        DecreaseRenderQueue(objects, SelectedObject);
    }
    ImGui::SameLine();
    static bool ShowQueue = false;
    ImGui::Checkbox("Show\nQueue", &ShowQueue);
    ShowRenderQueue(objects, SelectedObject,ShowQueue);
    
    
}


void ImGui::GeneralMenu(std::map<std::string, GameObject>& GameObjects, GameObject*& SelectedObject ,Enum_WarningStatus &WarningLevel)
{
    ImGui::SetNextWindowPos({ 0,0 });
    
    if (ImGui::Begin("GeneralMenu", (bool*)0, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize))
    {
        
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
        static bool ShouldObjectDeleted = false;
        static bool AddObjectButton = false;
        if(ImGui::Button("Add Objects"))
        {
            AddObjectButton = true;
        }
        ImGui::SameLine();
        if(ImGui::Button("Delete Objects") || ShouldObjectDeleted)
        {
            WarningLevel = DeleteSelectedObject(GameObjects,SelectedObject ,ShouldObjectDeleted);
        }

        if (AddObjectButton || ShouldObjectCreated)
        {
            WarningLevel = CreateNewObject(ShouldObjectCreated, GameObjects);
            AddObjectButton = false;
        }

        static std::string TextureName = "Textures";
        std::string TexturePath;
       
        
        
        
        ImGui::Separator();
        static bool ShowAllHitboxs = false;
        ImGui::Checkbox("Show Hitboxs", &ShowAllHitboxs);  
        
        
        ImGui::End();
    }


}


void ImGui::HitboxMenu(std::map<std::string, GameObject>& objects, GameObject*& SelectedObject)
{
    
    static std::string name_RecSelector = "rec";
    static std::string name_TriSelector = "tri";
    
    ImGui::Checkbox("Show Hitbox", &SelectedObject->ShouldHitboxDisplay);
    ImGui::SameLine();
    if (ImGui::Button("Reset Hitbox")) SelectedObject->ResetHitbox();
    ImGui::Spacing();
    ImGui::Text("IncreaseValue = %d", SelectedObject->MoveValue);
    ImGui::SameLine();
    if (ImGui::ArrowButton("left", ImGuiDir_Left) && SelectedObject->MoveValue != 1) { SelectedObject->MoveValue--; }
    ImGui::SameLine();
    if (ImGui::ArrowButton("right", ImGuiDir_Right) && SelectedObject->MoveValue != 5) { SelectedObject->MoveValue++; }
    
    
    
    if (ImGui::Button("Add Rec"))
        SelectedObject->Hitbox.recs.push_back(Rectanglex(numbers(SelectedObject->Hitbox.recs.size()), 400, 200, SelectedObject->Texture.width, SelectedObject->Texture.height));
    
    ImGui::SameLine();
    if (ImGui::Button("Add Tri"))
        SelectedObject->Hitbox.triangles.push_back(Triangle(numbers(SelectedObject->Hitbox.triangles.size()), { 200,200 }, { 400,200 }, { 300,100 }));

    
    ImGui::Separator();
    
    if (ImGui::TreeNode("Hitboxs"))
    {
        if (!SelectedObject->Hitbox.recs.empty() && ImGui::TreeNode("Rectangle"))
        {
            for (int i = 0; i < SelectedObject->Hitbox.recs.size(); i++)
            {
                if (ImGui::Selectable(toString(SelectedObject->Hitbox.recs[i].name).c_str()))
                {
                    SelectedObject->Hitbox.SelectedHitboxs.SelectedShape = enum_Rectangle;
                    SelectedObject->Hitbox.SelectedHitboxs.SelectedHitbox = SelectedObject->Hitbox.recs[i].name;
                }
            }
            ImGui::TreePop();
        }
        ImGui::Spacing();
        if (!SelectedObject->Hitbox.triangles.empty() && ImGui::TreeNode("Triangle"))
        {
            for (int i = 0; i < SelectedObject->Hitbox.triangles.size(); i++)
            {
                if (ImGui::Selectable(toString(SelectedObject->Hitbox.triangles[i].name).c_str()))
                {
                    SelectedObject->Hitbox.SelectedHitboxs.SelectedShape = enum_Triangle;
                    SelectedObject->Hitbox.SelectedHitboxs.SelectedHitbox = SelectedObject->Hitbox.triangles[i].name;
                }
            }
            ImGui::TreePop();
        }
        
        
        ImGui::TreePop();
    }
    

}

void ImGui::ObjectMenu(std::map<std::string, GameObject>& objects, GameObject*& SelectedObject)
{
    enum Menus { TextureMenu, HitboxMenu };
    
    static Menus menu = TextureMenu;
    static ImVec2 ObjectMenuWindowSize = {};
    static std::string MenuName = "ObjectMenu";
    
    if(SelectedObject != nullptr)
        MenuName = SelectedObject->ObjectName;
    else
        MenuName = "ObjectMenu";
    

    ImGui::SetNextWindowPos({ GetScreenWidth() - ObjectMenuWindowSize.x,0 });
    

    
    if(ImGui::Begin(MenuName.c_str(), (bool*)0, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar))
    {
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::SmallButton("Texture"))
                menu = TextureMenu;
            
            if (ImGui::SmallButton("Hitboxs"))
                menu = HitboxMenu;
            
            ImGui::EndMenuBar();
        }
        ImGui::Text("Move :>");
        ImGui::SameLine();
       
        
        
        
        if(SelectedObject != nullptr)
            ImGui::SwitchBox("Object", "Hitbox", SelectedObject->ShouldObjectOrHitboxMove);
        
        
        for (auto& object : objects)
        {
            object.second.ShouldObjectOrHitboxMove = SelectedObject->ShouldObjectOrHitboxMove;
        }
        
        
        
        
        
        switch (menu)
        {
        case TextureMenu: 
        {
            ImGui::TextureMenu(objects, SelectedObject);
        }
            break;
        case HitboxMenu:
        {
            ImGui::HitboxMenu(objects, SelectedObject);
            ImGui::HitboxInfo(SelectedObject);
        }
            break;
        default:
            break;
        }

        
        
        ObjectMenuWindowSize = ImGui::GetWindowSize();
        ImGui::End();
    }
    


}

void ImGui::TextureInfo(GameObject*& SelectedObject)
{
    
    ImGui::Text("Texture");
    
    ImGui::PushItemWidth(40);
    ImGui::InputFloat(" = X", &SelectedObject->Data.pos.x,0.0f,0.0f,"%.0f");
    ImGui::SameLine(100);
    ImGui::InputInt(" = Width", &SelectedObject->Texture.width,0,0 , ImGuiInputTextFlags_ReadOnly);
    ImGui::InputFloat(" = Y ", &SelectedObject->Data.pos.y, 0.0f, 0.0f, "%.0f");
    ImGui::SameLine(100);
    ImGui::InputInt(" = Height ", &SelectedObject->Texture.height, 0, 0);
    ImGui::PushItemWidth(132);
    ImGui::SliderFloat(" = Scale", &SelectedObject->Data.TextureScale, 0.5f, 3.0f,"%.1f",ImGuiInputTextFlags_ReadOnly);
    SelectedObject->UpdateTextureSize();
    
  
}





void ImGui::HitboxInfo(GameObject*& SelectedObject)
{
    ImGui::Text("Hitbox");
     
    
    switch (SelectedObject->Hitbox.SelectedHitboxs.SelectedShape)
    {
        case enum_Rectangle:
        {
            ImGui::PushItemWidth(40);
            ImGui::InputInt(" = X", &SelectedObject->Hitbox.recs[HITBOXINDEX].x,0,0);
            ImGui::SameLine(0,15);
            ImGui::InputInt(" = Width", &SelectedObject->Hitbox.recs[HITBOXINDEX].width, 0, 0, ImGuiInputTextFlags_ReadOnly);
            ImGui::InputInt(" = Y ", &SelectedObject->Hitbox.recs[HITBOXINDEX].y,0,0);
            ImGui::SameLine();
            ImGui::InputInt(" = Height ", &SelectedObject->Hitbox.recs[HITBOXINDEX].height,0,0);
            //ImGui::PushItemWidth(132);
            //ImGui::SliderFloat(" = Scale", &SelectedObject->Data.TextureScale, 0.5f, 3.0f, "%.1f", ImGuiInputTextFlags_ReadOnly);



            break;
        }
        case enum_Triangle:
        {
            
            
            
            break;
        }
        
    
    
    
    default:
        break;
    }





}




