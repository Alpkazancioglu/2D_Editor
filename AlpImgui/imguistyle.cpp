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
    ImGui::Text("IncreaseValue = %d",SelectedObject->Global.MoveValue);
    ImGui::SameLine();
    if (ImGui::ArrowButton("IncreaseLeft", ImGuiDir_Left) && SelectedObject->Global.MoveValue != 1) { SelectedObject->Global.MoveValue--; }
    ImGui::SameLine();
    if (ImGui::ArrowButton("IncreaseRight", ImGuiDir_Right) && SelectedObject->Global.MoveValue != 5) { SelectedObject->Global.MoveValue++; }
    ImGui::Separator();    
    ImGui::TextureInfo(SelectedObject);
    UpdateTextureSize(objects);
    
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
        ImGui::Checkbox("Show Hitboxs", &SelectedObject->Global.ShowAllHitboxs);  
        ImGui::Separator();
        if(Button("Save"))
        {    
            /*if (SAVEFILE::WriteSaveFile(GetRelativePath("/Saves/SaveFile.json").c_str(), GameObjects))
                WarningLevel = FileSaved;
            else
                WarningLevel = FileSavedFailed;*/
            WarningLevel = S_FileSelect;

        }
        ImGui::SameLine();
        if(Button("Load"))
        {
            
            /*if (SAVEFILE::ReadSaveFile(GetRelativePath("/Saves/SaveFile.json").c_str(), GameObjects, SelectedObject))
                WarningLevel = FileLoaded;
            else
                WarningLevel = FileLoadFailed;*/
            WarningLevel = L_FileSelect;
            
        }

        
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
    ImGui::Text("IncreaseValue = %d", SelectedObject->Global.MoveValue);
    ImGui::SameLine();
    if (ImGui::ArrowButton("left", ImGuiDir_Left) && SelectedObject->Global.MoveValue != 1) { SelectedObject->Global.MoveValue--; }
    ImGui::SameLine();
    if (ImGui::ArrowButton("right", ImGuiDir_Right) && SelectedObject->Global.MoveValue != 5) { SelectedObject->Global.MoveValue++; }
    
    
    
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
                    SelectedObject->Hitbox.SelectedHitboxs.SelectedShape = HitboxShape::Rectangle;
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
                    SelectedObject->Hitbox.SelectedHitboxs.SelectedShape = HitboxShape::Triangle;
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
            ImGui::SwitchBox("Object", "Hitbox", SelectedObject->Global.ShouldObjectOrHitboxMove);
         
       
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
    
    
  
}





void ImGui::HitboxInfo(GameObject*& SelectedObject)
{
    ImGui::Text("Hitbox");
     
    
    switch (SelectedObject->Hitbox.SelectedHitboxs.SelectedShape)
    {
        case HitboxShape::Rectangle:
        {
            if(!SelectedObject->Hitbox.recs.empty())
            {
                ImGui::PushItemWidth(40);
                ImGui::InputInt(" = X", &SelectedObject->Hitbox.recs[HITBOXINDEX].x, 0, 0);
                ImGui::SameLine(0, 15);
                ImGui::InputInt(" = Width", &SelectedObject->Hitbox.recs[HITBOXINDEX].width, 0, 0, ImGuiInputTextFlags_ReadOnly);
                ImGui::InputInt(" = Y ", &SelectedObject->Hitbox.recs[HITBOXINDEX].y, 0, 0);
                ImGui::SameLine();
                ImGui::InputInt(" = Height ", &SelectedObject->Hitbox.recs[HITBOXINDEX].height, 0, 0);
            }
            

            break;
        }
        case HitboxShape::Triangle:
        {
            if (!SelectedObject->Hitbox.triangles.empty())
            {
                ImGui::Text("V1 => ");
                ImGui::SameLine();
                ImGui::PushItemWidth(40);
                ImGui::InputFloat(" = X", &SelectedObject->Hitbox.triangles[HITBOXINDEX].v1.x, 0, 0, "%.0f", ImGuiInputTextFlags_ReadOnly);
                ImGui::SameLine();
                ImGui::InputFloat(" = Y", &SelectedObject->Hitbox.triangles[HITBOXINDEX].v1.y, 0, 0, "%.0f", ImGuiInputTextFlags_ReadOnly);
                ImGui::PopItemWidth();

                ImGui::Text("V2 => ");
                ImGui::SameLine();
                ImGui::PushItemWidth(40);
                ImGui::InputFloat(" = X", &SelectedObject->Hitbox.triangles[HITBOXINDEX].v2.x, 0, 0, "%.0f", ImGuiInputTextFlags_ReadOnly);
                ImGui::SameLine();
                ImGui::InputFloat(" = Y", &SelectedObject->Hitbox.triangles[HITBOXINDEX].v2.y, 0, 0, "%.0f", ImGuiInputTextFlags_ReadOnly);
                ImGui::PopItemWidth();

                ImGui::Text("V3 => ");
                ImGui::SameLine();
                ImGui::PushItemWidth(40);
                ImGui::InputFloat(" = X", &SelectedObject->Hitbox.triangles[HITBOXINDEX].v3.x, 0, 0, "%.0f", ImGuiInputTextFlags_ReadOnly);
                ImGui::SameLine();
                ImGui::InputFloat(" = Y", &SelectedObject->Hitbox.triangles[HITBOXINDEX].v3.y, 0, 0, "%.0f"), ImGuiInputTextFlags_ReadOnly;


            }
            
            
            break;
        }
        
    
    
    
    default:
        break;
    }





}

void ImGui::CameraInfo(Camera2D camera)
{
    
    if (IsKeyDown(KEY_LEFT_SHIFT))
    {
        static ImVec2 CameraInfoWindow = {};
        ImGui::SetNextWindowPos({ GetScreenWidth() - CameraInfoWindow.x ,GetScreenHeight() - CameraInfoWindow.y });
        if(ImGui::Begin("Camera",(bool*)0, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImGui::Text("Mouse Position = %.f , %.f ", GetScreenToWorld2D(GetMousePosition(), camera).x, GetScreenToWorld2D(GetMousePosition(), camera).y);
            ImGui::Text("Zoom = %.1f", camera.zoom);
            CameraInfoWindow = GetWindowSize();
            
            ImGui::End();
        }
        
    }
}




