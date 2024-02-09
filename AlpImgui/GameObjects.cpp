#include "GameObjects.h"

GameObject::GameObject()
{
	
}

GameObject::GameObject(std::string name)
{
	this->ObjectName = name;
	this->Data.pos = { 200,200 };
	this->Locked = false;
	
	
}



GameObject::GameObject(char name)
{
	this->ObjectName = name;
	this->Data.pos = { 200,200 };
	
}

GameObject::~GameObject()
{
	std::cout << "ObjectDeleted" << std::endl;
	
	UnloadTexture(Texture);
}

void GameObject::MoveHitbox(struct_SelectedHitboxs Data, Camera2D camera ,int value)
{

	switch (Data.SelectedShape)
	{

	case  HitboxShape::Rectangle:

		if (!this->Hitbox.recs.empty())
		{
			if (IsKeyPressed(KEY_D)) this->Hitbox.recs[Data.SelectedHitbox].x += value;
			else if (IsKeyPressed(KEY_A)) this->Hitbox.recs[Data.SelectedHitbox].x -= value;
			else if (IsKeyPressed(KEY_W)) this->Hitbox.recs[Data.SelectedHitbox].y -= value;
			else if (IsKeyPressed(KEY_S)) this->Hitbox.recs[Data.SelectedHitbox].y += value;
			else if (IsKeyPressed(KEY_RIGHT)) this->Hitbox.recs[Data.SelectedHitbox].width += value;
			else if (IsKeyPressed(KEY_LEFT)) this->Hitbox.recs[Data.SelectedHitbox].width -= value;
			else if (IsKeyPressed(KEY_UP)) this->Hitbox.recs[Data.SelectedHitbox].height -= value;
			else if (IsKeyPressed(KEY_DOWN)) this->Hitbox.recs[Data.SelectedHitbox].height += value;

			static bool hold = false;
			if (CollisionMouseWithRec(GetScreenToWorld2D(GetMousePosition(), camera), this->Hitbox.recs[Data.SelectedHitbox]) || hold)
			{

				if (ImGui::IsMouseDown(ImGuiMouseButton_Left))
				{
					//std::cout << HoldPosition.x << std::endl;
					this->Hitbox.recs[Data.SelectedHitbox].x += GetMouseDelta().x / camera.zoom;
					this->Hitbox.recs[Data.SelectedHitbox].y += GetMouseDelta().y / camera.zoom;
					hold = true;
				}
				else hold = false;
			}
		}
		break;


	case HitboxShape::Triangle:

		if (!this->Hitbox.triangles.empty())
		{
			if (IsKeyPressed(KEY_D))
			{
				this->Hitbox.triangles[Data.SelectedHitbox].v1.x += value;
				this->Hitbox.triangles[Data.SelectedHitbox].v2.x += value;
				this->Hitbox.triangles[Data.SelectedHitbox].v3.x += value;

			}

			else if (IsKeyPressed(KEY_A))
			{
				this->Hitbox.triangles[Data.SelectedHitbox].v1.x -= value;
				this->Hitbox.triangles[Data.SelectedHitbox].v2.x -= value;
				this->Hitbox.triangles[Data.SelectedHitbox].v3.x -= value;
			}
			else if (IsKeyPressed(KEY_W))
			{
				this->Hitbox.triangles[Data.SelectedHitbox].v1.y -= value;
				this->Hitbox.triangles[Data.SelectedHitbox].v2.y -= value;
				this->Hitbox.triangles[Data.SelectedHitbox].v3.y -= value;

			}
			else if (IsKeyPressed(KEY_S))
			{
				this->Hitbox.triangles[Data.SelectedHitbox].v1.y += value;
				this->Hitbox.triangles[Data.SelectedHitbox].v2.y += value;
				this->Hitbox.triangles[Data.SelectedHitbox].v3.y += value;

			}

			static bool hold = false;
			if (CheckCollisionPointTriangle(GetScreenToWorld2D(GetMousePosition(),camera), this->Hitbox.triangles[Data.SelectedHitbox].v1, this->Hitbox.triangles[Data.SelectedHitbox].v2, this->Hitbox.triangles[Data.SelectedHitbox].v3) || hold)
			{

				std::cout << "collision" << std::endl;
				if (ImGui::IsMouseDown(ImGuiMouseButton_Left))
				{

					this->Hitbox.triangles[Data.SelectedHitbox].v1.x += GetMouseDelta().x / camera.zoom;
					this->Hitbox.triangles[Data.SelectedHitbox].v1.y += GetMouseDelta().y / camera.zoom;
					this->Hitbox.triangles[Data.SelectedHitbox].v2.x += GetMouseDelta().x / camera.zoom;
					this->Hitbox.triangles[Data.SelectedHitbox].v2.y += GetMouseDelta().y / camera.zoom;
					this->Hitbox.triangles[Data.SelectedHitbox].v3.x += GetMouseDelta().x / camera.zoom;
					this->Hitbox.triangles[Data.SelectedHitbox].v3.y += GetMouseDelta().y / camera.zoom;
					hold = true;
				
				}
				else
					hold = false;

			}
		}
		break;


	}


}

bool CollisionMouseWithRec(Vector2 mouse,Rectanglex rec)
{
	return mouse.x > rec.x && mouse.x < (rec.x + rec.width) && mouse.y > rec.y && mouse.y < rec.y + rec.height;
}



bool CollisionMouseWithTexture(Vector2 mouse, ObjectData object, Texture2D Texture)
{
	return mouse.x > object.pos.x && mouse.x < (object.pos.x + Texture.width) && mouse.y > object.pos.y && mouse.y < object.pos.y + Texture.height;
}



void SetPrioarity(std::map<std::string, GameObject>& objects,GameObject* &SelectedObject)
{
	
	if( ImGui::IsKeyDown(ImGuiKey_LeftAlt))
	{
		if (ImGui::IsKeyReleased(ImGuiKey_DownArrow))
		{
			if (SelectedObject->RenderQueue != 0)
			{
				SelectedObject->RenderQueue--;

				for (auto& it : objects)
				{
					if ((it.second.ObjectName != SelectedObject->ObjectName) && (it.second.RenderQueue == SelectedObject->RenderQueue))
					{
						it.second.RenderQueue++;
						break;
					}
				}

			}
			
		}
		if(ImGui::IsKeyReleased(ImGuiKey_UpArrow))
		{
			
			if (SelectedObject->RenderQueue != objects.size()-1)
			{
				
				SelectedObject->RenderQueue++;
				
				for (auto& it : objects)
				{
					if ( (it.second.ObjectName != SelectedObject->ObjectName) && (it.second.RenderQueue == SelectedObject->RenderQueue))
					{
						it.second.RenderQueue--;
						break;
					}
				}
				
			}
		}
	}



	
}


void IncreaseRenderQueue(std::map<std::string, GameObject>& objects, GameObject*& SelectedObject)
{
	if (SelectedObject->RenderQueue != 0)
	{
		SelectedObject->RenderQueue--;

		for (auto& it : objects)
		{
			if ((it.second.ObjectName != SelectedObject->ObjectName) && (it.second.RenderQueue == SelectedObject->RenderQueue))
			{
				it.second.RenderQueue++;
				break;
			}
		}

	}
}

void DecreaseRenderQueue(std::map<std::string, GameObject>& objects, GameObject*& SelectedObject)
{
	if (SelectedObject->RenderQueue != objects.size() - 1)
	{
		SelectedObject->RenderQueue++;
		for (auto& it : objects)
		{
			if ((it.second.ObjectName != SelectedObject->ObjectName) && (it.second.RenderQueue == SelectedObject->RenderQueue))
			{
				it.second.RenderQueue--;
				break;
			}
		}

	}
}

void CreateNullObject(std::map<std::string, GameObject>& objects)
{
		objects["NULL"] = GameObject("NULL");
}

void DeleteNullObject(std::map<std::string, GameObject>& objects)
{
	if (objects.find("NULL") != objects.end())
		objects.erase("NULL");
}

void DrawObjects(const std::map<std::string, GameObject>& objects,bool DrawAll)
{
	
	
	for (int i = 0; i < objects.size(); i++)
	{
		static int j = 0;
		for (auto& object : objects)
		{
			if (object.second.RenderQueue == j)
			{
				DrawTextureEx(object.second.Texture, object.second.Data.pos, object.second.Data.rotation,1, WHITE);
				j++;
				break;
			}
		}
		if (j > objects.size() - 1) j = 0;
	}
}

void DrawHitboxs(std::map<std::string, GameObject>& objects, GameObject*& SelectedObject, bool DrawAll)
{
	if(!DrawAll)
	{
		if (SelectedObject->ShouldHitboxDisplay)
		{
			for (int i = 0; i < SelectedObject->Hitbox.recs.size(); i++)
			{
				DrawRectangleLinesEx(SelectedObject->Hitbox.recs[i].ConvertRec(), 1.0f, WHITE);
			}
		}
		if (SelectedObject->ShouldHitboxDisplay)
		{
			for (int i = 0; i < SelectedObject->Hitbox.triangles.size(); i++)
			{
				DrawTriangleLines(SelectedObject->Hitbox.triangles[i].v1, SelectedObject->Hitbox.triangles[i].v2, SelectedObject->Hitbox.triangles[i].v3, WHITE);
			}
		}
	}
	else
	{
		for (auto& object : objects)
		{

			if (!object.second.Hitbox.recs.empty())
			{
				for (int i = 0; i < object.second.Hitbox.recs.size(); i++)
				{
					DrawRectangleLinesEx(object.second.Hitbox.recs[i].ConvertRec(), 1.0f, WHITE);
				}

			}

			if(!object.second.Hitbox.triangles.empty())
			{
				for (int i = 0; i < object.second.Hitbox.triangles.size(); i++)
				{
					DrawTriangleLines(object.second.Hitbox.triangles[i].v1, object.second.Hitbox.triangles[i].v2, object.second.Hitbox.triangles[i].v3, WHITE);
				}
			}

		}
	}
	
}

void SelectObjectWithMouse(std::map<std::string,GameObject>& objects,GameObject* &pointer,Camera2D camera)
{
	if(IsKeyDown(KEY_LEFT_ALT) && ImGui::IsMouseDown(ImGuiMouseButton_Left))
	{
		for(auto& object : objects)
		{
			if (CollisionMouseWithTexture(GetScreenToWorld2D({ GetMousePosition().x , GetMousePosition().y },camera), object.second.Data, object.second.Texture))
			{
				std::cout << "succecs" << std::endl;
				pointer = &object.second;
			}
		}
	}		

}

void ShowRenderQueue(std::map<std::string, GameObject>& objects, GameObject*& SelectedObject,bool ShowQueue)
{
	if (ShowQueue)
	{
		ImGui::Separator();
		for (int i = 0; i < objects.size(); i++)
		{
			static int j = 0;
			for (auto& object : objects)
			{
				if (object.second.RenderQueue == j)
				{
					
					ImGui::Text("%s  =>  %d", object.second.ObjectName, object.second.RenderQueue);
					j++;
					break;
				}
			}
			if (j > objects.size() - 1) j = 0;
		}
		ImGui::Separator();
	}
	else
		return;
	
	 

}


void SelectHitboxWithMouse(GameObject*& SelectedObject, Camera2D camera)
{
	if (IsKeyDown(KEY_LEFT_ALT) && ImGui::IsMouseDown(ImGuiMouseButton_Left))
	{

		for (int i = 0; i < SelectedObject->Hitbox.recs.size(); i++)
		{
			if (CollisionMouseWithRec(GetScreenToWorld2D(GetMousePosition(), camera), SelectedObject->Hitbox.recs[i]))
			{
				SelectedObject->Hitbox.SelectedHitboxs.SelectedShape = HitboxShape::Rectangle;
				SelectedObject->Hitbox.SelectedHitboxs.SelectedHitbox = SelectedObject->Hitbox.recs[i].name;
				return;
			}
		}

		for (int i = 0; i < SelectedObject->Hitbox.triangles.size(); i++)
		{
			if (CheckCollisionPointTriangle(GetScreenToWorld2D(GetMousePosition(), camera), SelectedObject->Hitbox.triangles[i].v1, SelectedObject->Hitbox.triangles[i].v2, SelectedObject->Hitbox.triangles[i].v3))
			{
				SelectedObject->Hitbox.SelectedHitboxs.SelectedShape = HitboxShape::Triangle;
				SelectedObject->Hitbox.SelectedHitboxs.SelectedHitbox = SelectedObject->Hitbox.triangles[i].name;
				return;
			}
		}

	}

}


void GameObject::MoveObject(Camera2D camera,unsigned int value)
{
	if (IsKeyDown(KEY_D)) Data.pos.x += value;
	else if (IsKeyDown(KEY_A)) Data.pos.x -= value;
	else if (IsKeyDown(KEY_W)) Data.pos.y -= value;
	else if (IsKeyDown(KEY_S)) Data.pos.y += value;
	
	static bool hold = false;
	if (CollisionMouseWithTexture(GetScreenToWorld2D({ ImGui::GetMousePos().x,ImGui::GetMousePos().y },camera),this->Data,this->Texture) || hold)
	{
		
		if (ImGui::IsMouseDown(ImGuiMouseButton_Left))
		{
			Data.pos.x += GetMouseDelta().x / camera.zoom;
			Data.pos.y += GetMouseDelta().y / camera.zoom;
			hold = true;
			std::cout << "succecs\n";
		}
		else
		{
			hold = false;
		}
		
	}
	Data.IsMoving = hold;
}

void GameObject::ResetHitbox()
{
	for (int i = 0; i < this->Hitbox.recs.size(); i++)
	{
		Hitbox.recs[i].x = Data.pos.x;
		Hitbox.recs[i].y = Data.pos.y;
		Hitbox.recs[i].width = Texture.width;
		Hitbox.recs[i].height = Texture.height;
	}
}

std::string GetRelativePath(std::string TextureName)
{
	std::string WorkingDir(GetWorkingDirectory());

	for (size_t i = 0; i < WorkingDir.size(); i++)
	{
		if (WorkingDir.at(i) == '\\') {
			WorkingDir.at(i) = '/';
		}
	}
	 std::string TexturePath(WorkingDir + "/Textures/" + TextureName);
	 return TexturePath;
}
std::string GetRelativePath()
{
	std::string WorkingDir(GetWorkingDirectory());

	for (size_t i = 0; i < WorkingDir.size(); i++)
	{
		if (WorkingDir.at(i) == '\\') {
			WorkingDir.at(i) = '/';
		}
	}
	std::string TexturePath(WorkingDir + "/Textures/");
	return TexturePath;
}

std::vector<std::pair<std::string, std::string>> ReadMultipleFilesFromDirectory(const char* FilePathToDirectory)
{

	std::vector<std::pair<std::string, std::string>> result;
	std::string path = FilePathToDirectory;
	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		std::string PathDirect = entry.path().generic_string().c_str();
		if (IsFileExtension(PathDirect.c_str(), ".png"))
		{
			std::string PathName;
			if (PathDirect.find('/') != std::string::npos)
			{
				PathName = strrchr(PathDirect.c_str(), '/') + 1;
			}
			else if (PathDirect.find('\\') != std::string::npos)
			{
				PathName = strrchr(PathDirect.c_str(), '\\') + 1;
			}
			result.push_back({ PathName,entry.path().generic_string().c_str() });
		}
		else
			std::cout << "failed!!!!!!!!" << std::endl;

	}

	return result;

}



Enum_WarningStatus CreateNewObject(bool& active, std::map<std::string, GameObject>& object)
{
	
	active = true;
	static char ObjectName[20] = {};
	ImGui::InputText("Object Name", ObjectName, IM_ARRAYSIZE(ObjectName));
	auto Textures = ReadMultipleFilesFromDirectory(GetRelativePath().c_str());
	
	static std::string TextureName = "Textures";
	static std::string TexturePath;
	
	if(ImGui::BeginCombo("Textures",TextureName.c_str()))
	{
		for (size_t i = 0; i < Textures.size(); i++)
		{
			if (ImGui::Selectable(Textures[i].first.c_str()))
			{
				TexturePath = Textures[i].second;
				TextureName = Textures[i].first;
			}

		}
		ImGui::EndCombo();
	}
	
	
	
	if(ImGui::Button("Create"))
	{
		
		std::cout << TextureName << " :: " << TexturePath << std::endl;
		if(object.find(ObjectName) == object.end())
		{
			object[ObjectName] = GameObject(ObjectName);
			object[ObjectName].Texture = LoadTexture(TexturePath.c_str());
			
			if (!IsTextureReady(object[ObjectName].Texture))
			{	
				object.erase(ObjectName);
				*ObjectName = {};
				//*TextureName = {};
				active = false;
				return TextureFailed;
			}
			else
			{
				object[ObjectName].Data.OriginalTextureSize = { (float)object[ObjectName].Texture.width,(float)object[ObjectName].Texture.height };
				object[ObjectName].RenderQueue = Iterator;
				Iterator++;
				active = false;
				DeleteNullObject(object);

			}

		}
		else
		{
			std::cout << "object already created" << std::endl;
			*ObjectName = {};
			//*TextureName = {};
			active = false;
			return ObjectCreatingFailed;
			
		}
		*ObjectName = {};
		//*TextureName = {};
		active = false;
		return Succeed;
		
	}
	
	ImGui::SameLine();
	if (ImGui::Button("Cancel")) 
	{
		*ObjectName = {};
		//*TextureName = {};
		active = false;
		return Succeed;
		
	}
	ImGui::Spacing();
	return Succeed;

}

Enum_WarningStatus DeleteSelectedObject(std::map<std::string, GameObject>& objects,GameObject*& SelectedObject,bool &active)
{
	
	active = true;
	ImGui::OpenPopup("     Wait A Minute  ");
	// Always center this window when appearing
	ImVec2 center = { (float)GetScreenWidth() / 2,(float)GetScreenHeight() / 2 };
	ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

	if (ImGui::BeginPopupModal("     Wait A Minute  ", NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text("Are You Sure ? %s will be deleted",SelectedObject->ObjectName.c_str());
		ImGui::Separator();

		
		if (ImGui::Button("Yes", ImVec2(120, 0)))
		{
			
			
			if (SelectedObject->RenderQueue != objects.size() - 1)
			{
				while(SelectedObject->RenderQueue != objects.size()-1)
				{
					SelectedObject->RenderQueue++;
					for (auto& it : objects)
					{
						if ((it.second.ObjectName != SelectedObject->ObjectName) && (it.second.RenderQueue == SelectedObject->RenderQueue))
						{
							it.second.RenderQueue--;
							break;
						}
					}
				}
			}
		
			objects.erase(SelectedObject->ObjectName);
			if(objects.empty())
				CreateNullObject(objects);
			Iterator--;

			ImGui::CloseCurrentPopup();
			active = false;
			return ObjectDeleted;
			
		}
		ImGui::SameLine();
		if (ImGui::Button("No", ImVec2(120, 0)))
		{
			active = false;
			ImGui::CloseCurrentPopup();
		}
		
		ImGui::SetItemDefaultFocus();
		ImGui::EndPopup();
		return Succeed;
	}



	
	return Succeed;
}






void GameObject::ShowHitbox(bool active)
{

}

Vector2 ObjectData::ToScreenCoord()
{
	Vector2 ScreenMidPoint = { (float)GetScreenWidth() / 2,(float)GetScreenHeight() / 2 };
	Vector2 MidPointMouseDelta = { GetMouseX() - ScreenMidPoint.x , GetMouseY() - ScreenMidPoint.y };

	return { pos.x - MidPointMouseDelta.x , pos.y - MidPointMouseDelta.y };
}

void GameObject::UpdateTextureSize()
{
	
	Texture.width = Data.OriginalTextureSize.x * Data.TextureScale;
	Texture.height = Data.OriginalTextureSize.y * Data.TextureScale;

}

std::string toString(numbers name)
{
	switch (name)
	{
	case numbers::first: return "first";
		break;
	case numbers::second: return "second";
		break;
	case numbers::third: return "third";
		break;
	case numbers::fourth: return "fourth";
		break;
	case numbers::fifth: return "fifth";
		break;
	default:
		break;
	}
}
