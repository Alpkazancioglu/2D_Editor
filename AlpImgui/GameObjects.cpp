#include "GameObjects.h"

GameObject::GameObject()
{
	
}

GameObject::GameObject(std::string name)
{
	this->ObjectName = name;
	this->Data.pos = { 200,200 };
	static int Iterator = 0;
	this->RenderQueue = Iterator;
	Id = Iterator;
	Iterator++;
	this->Locked = false;
	
	
}

GameObject::GameObject(char name)
{
	this->ObjectName = name;
	this->Data.pos = { 200,200 };

}

GameObject::~GameObject()
{
	UnloadTexture(Texture);
}

void GameObject::MoveHitbox(unsigned int value, numbers name)
{
	if(!this->Hitbox.recs.empty())
	{
		if (IsKeyDown(KEY_D)) this->Hitbox.recs[name].x += value;
		else if (IsKeyDown(KEY_A)) this->Hitbox.recs[name].x -= value;
		else if (IsKeyDown(KEY_W)) this->Hitbox.recs[name].y -= value;
		else if (IsKeyDown(KEY_S)) this->Hitbox.recs[name].y += value;
		else if (IsKeyDown(KEY_RIGHT)) this->Hitbox.recs[name].width += value;
		else if (IsKeyDown(KEY_LEFT)) this->Hitbox.recs[name].width -= value;
		else if (IsKeyDown(KEY_UP)) this->Hitbox.recs[name].height -= value;
		else if (IsKeyDown(KEY_DOWN)) this->Hitbox.recs[name].height += value;

		static bool hold = false;
		if (CollisionMouseWithRec({ ImGui::GetMousePos().x,ImGui::GetMousePos().y }, this->Hitbox.recs[name]) || hold)
		{
			
		
			Vector2 mouse = { ImGui::GetMousePos().x,ImGui::GetMousePos().y };
			static Vector2 HoldMousePosition = {};
			static Vector2 HoldRecPosition = {};
			
			if (!hold)
			{
				HoldMousePosition = mouse;
				HoldRecPosition = {(float)Hitbox.recs[name].x, (float)Hitbox.recs[name].y};
			}
			
			if (ImGui::IsMouseDown(ImGuiMouseButton_Left))
			{
				//std::cout << HoldPosition.x << std::endl;
				this->Hitbox.recs[name].x = mouse.x - (HoldMousePosition.x - HoldRecPosition.x);
				this->Hitbox.recs[name].y = mouse.y - (HoldMousePosition.y - HoldRecPosition.y);
				hold = true;
			}
			else hold = false;


		}
	}
	


}

bool CollisionMouseWithRec(Vector2 mouse,Rectanglex rec)
{
	if (mouse.x > rec.x && mouse.x < (rec.x + rec.width) && mouse.y > rec.y && mouse.y < rec.y + rec.height) return true;
	
	return false;
}
bool CollisionMouseWithRec(Vector2 mouse, ObjectData object , Texture2D Texture)
{
	if (mouse.x > object.pos.x && mouse.x < (object.pos.x + Texture.width*object.TextureScale) && mouse.y > object.pos.y && mouse.y < object.pos.y + Texture.height*object.TextureScale) return true;

	return false;
}

void SetPrioarity(std::map<std::string, GameObject>& objects,GameObject* &SelectedObject)
{
	//GameObject* selectedObject;
	/*SelectObjectWithMouse(objects,SelectedObject);
	SelectedObject->RenderQueue = 0;
	int temp = 1;
	for (auto& it : objects)
	{

		if (it.second.Id != SelectedObject->Id)
		{
			it.second.RenderQueue = temp;
			temp++;
		}

	}*/
	
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

void DrawHitboxs(const std::map<std::string, GameObject>& objects, GameObject*& SelectedObject, bool DrawAll)
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
	}
	else
	{
		for(auto& object : objects)
		{
			if (object.second.ShouldHitboxDisplay)
			{
				for (int i = 0; i < object.second.Hitbox.recs.size(); i++)
				{
					DrawRectangleLinesEx(SelectedObject->Hitbox.recs[i].ConvertRec(), 1.0f, WHITE);
				}
			}
		}
	}
	
}

void SelectObjectWithMouse(std::map<std::string,GameObject>& objects,GameObject* &pointer)
{
	if(IsKeyDown(KEY_LEFT_ALT) && ImGui::IsMouseDown(ImGuiMouseButton_Left))
	{
		for(auto& object : objects)
		{
			if (CollisionMouseWithRec(GetMousePosition(), object.second.Data, object.second.Texture))
			{
				std::cout << "succecs" << std::endl;
				pointer = &object.second;
			}
		}
	}		

}
void SelectHitboxWithMouse(GameObject* &SelectedObject, numbers& HitboxFocus)
{
	if (IsKeyDown(KEY_LEFT_ALT) && ImGui::IsMouseDown(ImGuiMouseButton_Left))
	{
		for (int i = 0;i < SelectedObject->Hitbox.recs.size();i++)
		{
			if (CollisionMouseWithRec(GetMousePosition(), SelectedObject->Hitbox.recs[i]))
			{
				std::cout << "succecs" << std::endl;
				HitboxFocus = SelectedObject->Hitbox.recs[i].name;
			}
		}
	}

}




void GameObject::MoveObject(unsigned int value)
{
	if (IsKeyDown(KEY_D)) Data.pos.x += value;
	else if (IsKeyDown(KEY_A)) Data.pos.x -= value;
	else if (IsKeyDown(KEY_W)) Data.pos.y -= value;
	else if (IsKeyDown(KEY_S)) Data.pos.y += value;
	
	static bool hold = false;
	if (CollisionMouseWithRec({ ImGui::GetMousePos().x,ImGui::GetMousePos().y },Data,Texture) || hold)
	{


		Vector2 mouse = { ImGui::GetMousePos().x,ImGui::GetMousePos().y };
		static Vector2 HoldMousePosition = {};
		static Vector2 HoldTexturePosition = {};

		if (!hold)
		{
			HoldMousePosition = mouse;
			HoldTexturePosition = { (float)Data.pos.x, (float)Data.pos.y };
		}

		if (ImGui::IsMouseDown(ImGuiMouseButton_Left))
		{
			//std::cout << HoldPosition.x << std::endl;
			Data.pos.x = mouse.x - (HoldMousePosition.x - HoldTexturePosition.x);
			Data.pos.y = mouse.y - (HoldMousePosition.y - HoldTexturePosition.y);
			hold = true;
		}
		else hold = false;


	}
	
}

void GameObject::ResetHitbox()
{
	for (int i = 0; i < this->Hitbox.recs.size(); i++)
	{
		Hitbox.recs[i].x = Data.pos.x;
		Hitbox.recs[i].y = Data.pos.y;
		Hitbox.recs[i].width = Texture.width*Data.TextureScale;
		Hitbox.recs[i].height = Texture.height*Data.TextureScale;
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
	 std::string TexturePath(WorkingDir + "/Textures/" + TextureName + ".png");
	 return TexturePath;
}

Enum_WarningStatus CreateNewObject(bool& active, std::map<std::string, GameObject>& object)
{
	
	active = true;
	
	static char ObjectName[20] = {};
	static char TextureName[20] = {};
	ImGui::InputText("Object Name", ObjectName, IM_ARRAYSIZE(ObjectName));
	ImGui::InputText("Texture Name", TextureName, IM_ARRAYSIZE(TextureName));
	std::string TexturePath = GetRelativePath(TextureName);
	
	
	if(ImGui::Button("Create"))
	{
		if(object.find(ObjectName) == object.end())
		{
			object[ObjectName] = GameObject(ObjectName);
			object[ObjectName].Texture = LoadTexture(TexturePath.c_str());
			if (!IsTextureReady(object[ObjectName].Texture))
			{	
				object.erase(ObjectName);
				*ObjectName = {};
				*TextureName = {};
				active = false;
				return TextureFailed;
			}
			else active = false;
			object[ObjectName].Data.OriginalTextureSize = { (float)object[ObjectName].Texture.width,(float)object[ObjectName].Texture.height };
			
			

		}
		else
		{
			std::cout << "object already created" << std::endl;
			*ObjectName = {};
			*TextureName = {};
			active = false;
			return ObjectFailed;
			
		}
		*ObjectName = {};
		*TextureName = {};
		active = false;
		return Succeed;
		
	}
	
	ImGui::SameLine();
	if (ImGui::Button("Cancel")) 
	{
		*ObjectName = {};
		*TextureName = {};
		active = false;
		return Succeed;
		
	}
	ImGui::Spacing();
	return Succeed;


	
	
}






void GameObject::ShowHitbox(bool active)
{
}

void GameObject::UpdateTextureSize()
{
	
	Texture.width = Data.OriginalTextureSize.x * Data.TextureScale;
	Texture.height = Data.OriginalTextureSize.y * Data.TextureScale;

}

const char* toString(numbers name)
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
