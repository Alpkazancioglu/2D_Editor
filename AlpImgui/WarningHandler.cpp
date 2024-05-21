#include "WarningHandler.h"



void Warning::WarningHandler(Enum_WarningStatus& WarningStatus , std::map<std::string, GameObject>& GameObjects, GameObject*& selectedObject)
{
    if (WarningStatus == ObjectCreatingFailed)
        Warning::ObjectNotCreated(WarningStatus);
    if (WarningStatus == TextureFailed)
        Warning::TextureNotLoaded(WarningStatus);
    if (WarningStatus == ObjectDeleted)
        Warning::ObjectDelete(WarningStatus);
    if (WarningStatus == FileLoaded || WarningStatus == FileLoadFailed)
        Warning::FileLoad(WarningStatus);
    if (WarningStatus == FileSaved || WarningStatus == FileSavedFailed)
        Warning::FileSave(WarningStatus);
    if (WarningStatus == S_FileSelect || WarningStatus == L_FileSelect)
        Warning::FileSelector(WarningStatus,GameObjects,selectedObject);

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

void Warning::ObjectNotCreated(Enum_WarningStatus& WarningStatus)
{
    
    WarningStatus = ObjectCreatingFailed;
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

void Warning::FileSave(Enum_WarningStatus& WarningStatus)
{


    WarningStatus = FileSaved;
    ImGui::OpenPopup("    Yeeeey");

    // Always center this window when appearing
    ImVec2 center = { (float)GetScreenWidth() / 2,(float)GetScreenHeight() / 2 };
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

    if (ImGui::BeginPopupModal("    Yeeeey", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("File Is Saved");
        ImGui::Separator();


        if (ImGui::Button("OK", ImVec2(120, 0)))
        {
            ImGui::CloseCurrentPopup();
            WarningStatus = Succeed;
        }
        ImGui::SetItemDefaultFocus();

        ImGui::EndPopup();
    }

}

void Warning::FileLoad(Enum_WarningStatus& WarningStatus)
{
    WarningStatus = FileLoaded;
    ImGui::OpenPopup("    Yeeeey");

    // Always center this window when appearing
    ImVec2 center = { (float)GetScreenWidth() / 2,(float)GetScreenHeight() / 2 };
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

    if (ImGui::BeginPopupModal("    Yeeeey", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("File Is Loaded");
        ImGui::Separator();


        if (ImGui::Button("OK", ImVec2(120, 0)))
        {
            ImGui::CloseCurrentPopup();
            WarningStatus = Succeed;
        }
        ImGui::SetItemDefaultFocus();

        ImGui::EndPopup();
    }



}


void Warning::FileSelector(Enum_WarningStatus& WarningStatus, std::map<std::string, GameObject>& GameObjects, GameObject*& selectedObject)
{

    

    ImGui::OpenPopup("SelectFile");

    // Always center this window when appearing
    ImVec2 center = { (float)GetScreenWidth() / 2,(float)GetScreenHeight() / 2 };
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

    if (ImGui::BeginPopupModal("SelectFile", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("Object is deleted");
        ImGui::Separator();

        auto SaveFiles = FilePath::ReadMultipleFilesFromDirectory(FilePath::GetRelativePath("/Saves").c_str(), ".json");

        static std::string SelectedFileName = "Files";
        static std::string SelectedFilePath = "null";
        if (ImGui::BeginCombo("SaveFiles", SelectedFileName.c_str()))
        {
            for (size_t i = 0; i < SaveFiles.size(); i++)
            {
                if (ImGui::Selectable(SaveFiles[i].first.c_str()))
                {
                    SelectedFileName = SaveFiles[i].first.c_str();
                    SelectedFilePath = SaveFiles[i].second.c_str();
                }

            }
            ImGui::EndCombo();
        }

        if (WarningStatus == S_FileSelect)
        {
            if (ImGui::Button("Save"))
            {
                if (SAVEFILE::WriteSaveFile(SelectedFilePath.c_str(), GameObjects))
                    WarningStatus = FileSaved;

                else
                    WarningStatus = FileSavedFailed;
            }
            static bool creatingfile = false;
            ImGui::SameLine();
            if(ImGui::Button("Create New File") || creatingfile)
            {
                creatingfile = true;
                ImGui::OpenPopup("creatingfile");

                if (ImGui::BeginPopupModal("creatingfile", NULL, ImGuiWindowFlags_AlwaysAutoResize))
                {
                    
                    static char FileName[20] = {};
                    ImGui::InputText("File Name", FileName, IM_ARRAYSIZE(FileName));
                    


                    if(ImGui::Button("Create"))
                    {
                        std::string path = FilePath::GetRelativePath("/Saves/") + FileName + ".json";
                        std::cout << path << '\n';
                        std::ofstream file(path);
                        creatingfile = false;
                        file.close();
                            
                    }


                    if (ImGui::Button("Cancel"))
                    {
                        ImGui::CloseCurrentPopup();
                        creatingfile = false;
                        WarningStatus = Succeed;
                    }


                    ImGui::SetItemDefaultFocus();
                    ImGui::EndPopup();
                }

            }

        }
        else if (WarningStatus == L_FileSelect)
        {
            if (ImGui::Button("Load"))
            {
                if (SAVEFILE::ReadSaveFile(SelectedFilePath.c_str(), GameObjects, selectedObject))
                    WarningStatus = FileLoaded;

                else
                    WarningStatus = FileLoadFailed;
            }
        }

        ImGui::SameLine();
        if (ImGui::Button("Cancel"))
        {
            ImGui::CloseCurrentPopup();
            WarningStatus = Succeed;
        }


        ImGui::SetItemDefaultFocus();
        ImGui::EndPopup();
    }


}

void Warning::ObjectDelete(Enum_WarningStatus& WarningStatus)
{
    WarningStatus = ObjectDeleted;
    ImGui::OpenPopup("  Good Job");

    // Always center this window when appearing
    ImVec2 center = { (float)GetScreenWidth() / 2,(float)GetScreenHeight() / 2 };
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

    if (ImGui::BeginPopupModal("  Good Job", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("Object is deleted");
        ImGui::Separator();
        
        
        if (ImGui::Button("OK", ImVec2(120, 0)))
        {
            ImGui::CloseCurrentPopup();
            WarningStatus = Succeed;
        }
        ImGui::SetItemDefaultFocus();

        ImGui::EndPopup();
    }

}
