#include "SaveHandler.h"

void SAVEFILE::handler(std::map<std::string, GameObject>& GameObjects, GameObject*& SelectedObject)
{
	std::string SaveFileLocation = GetWorkingDirectory();
	SaveFileLocation += "/SaveFile.json";
	if (IsKeyPressed(KEY_K))
	{	
		SAVEFILE::WriteSaveFile(SaveFileLocation.c_str(), GameObjects);
	}
	if (IsKeyPressed(KEY_L))
	{
		SAVEFILE::ReadSaveFile(SaveFileLocation.c_str(), GameObjects, SelectedObject);
	}
}

bool SAVEFILE::IsFileEmpty(const char* filename)
{
	std::ifstream file(filename);
	return file.peek() == std::ifstream::traits_type::eof();
}

bool SAVEFILE::ReadSaveFile(const char* filename, std::map<std::string, GameObject>& GameObjects, GameObject* &selectedObject)
{
	
	GameObjects.clear();
	selectedObject = nullptr;
	
	std::ifstream file(filename);
	json SaveFile;
	
	file >> SaveFile;

	for(const auto& object : SaveFile.items())
	{
		GameObjects[object.key()] = GameObject(object.key());
		if (IsTextureReady(LoadTexture(FilePath::GetRelativeTexturePath(SaveFile[object.key()]["Texture"]["TextureName"]).c_str())))
		{
			GameObjects[object.key()].Texture = LoadTexture(FilePath::GetRelativeTexturePath(SaveFile[object.key()]["Texture"]["TextureName"]).c_str());
			GameObjects[object.key()].Data.OriginalTextureSize = {(float)GameObjects[object.key()].Texture.width,(float)GameObjects[object.key()].Texture.height};
		}
		
		GameObjects[object.key()].Data.pos.x = SaveFile[object.key()]["Texture"]["pos"]["x"];
		GameObjects[object.key()].Data.pos.y = SaveFile[object.key()]["Texture"]["pos"]["y"];
		GameObjects[object.key()].RenderQueue = SaveFile[object.key()]["Texture"]["RenderQueue"];
		GameObjects[object.key()].Data.TextureScale = SaveFile[object.key()]["Texture"]["TextureScale"];
		GameObjects[object.key()].Data.TextureName = SaveFile[object.key()]["Texture"]["TextureName"];

		if(SaveFile[object.key()].find("Hitboxs") != SaveFile[object.key()].end())
		{
			std::cout << "succecs\n";
			if(SaveFile[object.key()]["Hitboxs"].find("Recs") != SaveFile[object.key()]["Hitboxs"].end())
			{
				int i = 0;
				for(auto &recs : SaveFile[object.key()]["Hitboxs"]["Recs"].items())
				{
					Rectanglex rec = {numbers(i),recs.value()["x"],recs.value()["y"] ,recs.value()["width"] ,recs.value()["height"]};
					GameObjects[object.key()].Hitbox.recs.push_back(rec);
					i++;

				}
			}
			if (SaveFile[object.key()]["Hitboxs"].find("Triangles") != SaveFile[object.key()]["Hitboxs"].end())
			{
				int i = 0;
				for (auto& triangles : SaveFile[object.key()]["Hitboxs"]["Triangles"].items())
				{
					Triangle triangle = 
					{numbers(i), 
					{triangles.value()["v1"]["x"],triangles.value()["v1"]["y"]},
					{triangles.value()["v2"]["x"],triangles.value()["v2"]["y"]},
					{triangles.value()["v3"]["x"],triangles.value()["v3"]["y"]}
					};

					GameObjects[object.key()].Hitbox.triangles.push_back(triangle);
					i++;

				}
			}

		}

		if (selectedObject == nullptr)
			selectedObject = &GameObjects[object.key()];
			
	}
	file.close();
	return true;

}

bool SAVEFILE::WriteSaveFile(const char* filename, std::map<std::string, GameObject>& GameObjects)
{

	std::ofstream file(filename);

	json SaveFile;
	
	

	for (auto& objects : GameObjects)
	{
		SaveFile[objects.first]["Texture"]["pos"]["x"] = objects.second.Data.pos.x;
		SaveFile[objects.first]["Texture"]["pos"]["y"] = objects.second.Data.pos.y;
		SaveFile[objects.first]["Texture"]["TextureScale"] = objects.second.Data.TextureScale;
		SaveFile[objects.first]["Texture"]["RenderQueue"] = objects.second.RenderQueue;
		SaveFile[objects.first]["Texture"]["TextureName"] = objects.second.Data.TextureName;
		if(!objects.second.Hitbox.recs.empty())
		{
			for (size_t i = 0; i < objects.second.Hitbox.recs.size(); i++)
			{
				SaveFile[objects.first]["Hitboxs"]["Recs"][toString(objects.second.Hitbox.recs[i].name) + " Rec"]["x"] = objects.second.Hitbox.recs[i].x;
				SaveFile[objects.first]["Hitboxs"]["Recs"][toString(objects.second.Hitbox.recs[i].name) + " Rec"]["y"] = objects.second.Hitbox.recs[i].y;
				SaveFile[objects.first]["Hitboxs"]["Recs"][toString(objects.second.Hitbox.recs[i].name) + " Rec"]["width"] = objects.second.Hitbox.recs[i].width;
				SaveFile[objects.first]["Hitboxs"]["Recs"][toString(objects.second.Hitbox.recs[i].name) + " Rec"]["height"] = objects.second.Hitbox.recs[i].height;
				
			}
		}
		if(!objects.second.Hitbox.triangles.empty())
		{
			for (size_t i = 0; i < objects.second.Hitbox.triangles.size(); i++)
			{
				SaveFile[objects.first]["Hitboxs"]["Triangles"][toString(objects.second.Hitbox.triangles[i].name) + " Triangle"]["v1"]["x"] = objects.second.Hitbox.triangles[i].v1.x;
				SaveFile[objects.first]["Hitboxs"]["Triangles"][toString(objects.second.Hitbox.triangles[i].name) + " Triangle"]["v1"]["y"] = objects.second.Hitbox.triangles[i].v1.y;
				SaveFile[objects.first]["Hitboxs"]["Triangles"][toString(objects.second.Hitbox.triangles[i].name) + " Triangle"]["v2"]["x"] = objects.second.Hitbox.triangles[i].v2.x;
				SaveFile[objects.first]["Hitboxs"]["Triangles"][toString(objects.second.Hitbox.triangles[i].name) + " Triangle"]["v2"]["y"] = objects.second.Hitbox.triangles[i].v2.y;
				SaveFile[objects.first]["Hitboxs"]["Triangles"][toString(objects.second.Hitbox.triangles[i].name) + " Triangle"]["v3"]["x"] = objects.second.Hitbox.triangles[i].v3.x;
				SaveFile[objects.first]["Hitboxs"]["Triangles"][toString(objects.second.Hitbox.triangles[i].name) + " Triangle"]["v3"]["y"] = objects.second.Hitbox.triangles[i].v3.y;
			}
		}

	}

	file << std::setw(4) <<SaveFile;
	file.close();
	return true;

}
