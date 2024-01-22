#include "WarningHandler.h"



void Warning::WarningHandler(Enum_WarningStatus& WarningStatus)
{
    if (WarningStatus == ObjectFailed) Warning::ObjectNotLoaded(WarningStatus);
    if (WarningStatus == TextureFailed) Warning::TextureNotLoaded(WarningStatus);
}

void Warning::TextureNotLoaded(Enum_WarningStatus& WarningStatus)
{
    WarningStatus = TextureFailed;
    ImGui::OpenPopup("        Daaamn");

    // Always center this window when appearing
    ImVec2 center = { (float)GetScreenWidth() / 2,(float)GetScreenHeight() / 2 };
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

    if (ImGui::BeginPopupModal("        Daaamn", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("Texture is not loaded");
        ImGui::Separator();

        //static int unused_i = 0;
        //ImGui::Combo("Combo", &unused_i, "Delete\0Delete harder\0");

       

        if (ImGui::Button("OK", ImVec2(120, 0)))
        {
            ImGui::CloseCurrentPopup();
            WarningStatus = Succeed;
        }
        ImGui::SetItemDefaultFocus();

        ImGui::EndPopup();
    }
    
}

void Warning::ObjectNotLoaded(Enum_WarningStatus& WarningStatus)
{
    
    WarningStatus = ObjectFailed;
    ImGui::OpenPopup("        Daaamn");

    // Always center this window when appearing
    ImVec2 center = { (float)GetScreenWidth() / 2,(float)GetScreenHeight() / 2 };
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

    if (ImGui::BeginPopupModal("        Daaamn", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("This Object Already Created");
        ImGui::Separator();

        //static int unused_i = 0;
        //ImGui::Combo("Combo", &unused_i, "Delete\0Delete harder\0");

       

        if (ImGui::Button("OK", ImVec2(120, 0)))
        {
            ImGui::CloseCurrentPopup(); 
            WarningStatus = Succeed;
        }
        ImGui::SetItemDefaultFocus();
      
        ImGui::EndPopup();
    }
}
