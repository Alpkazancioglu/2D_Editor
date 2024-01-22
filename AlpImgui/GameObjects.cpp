#include "GameObjects.h"

GameObject::GameObject()
{
}

GameObject::GameObject(std::string name)
{
	this->ObjectName = name;
	this->Data.pos = { 200,200 };
	
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
	if (IsKeyDown(KEY_D)) this->Hitbox.recs[name].x += value;
	else if (IsKeyDown(KEY_A)) this->Hitbox.recs[name].x -= value;
	else if (IsKeyDown(KEY_W)) this->Hitbox.recs[name].y -= value;
	else if (IsKeyDown(KEY_S)) this->Hitbox.recs[name].y += value;
	else if (IsKeyDown(KEY_RIGHT)) this->Hitbox.recs[name].width += value;
	else if (IsKeyDown(KEY_LEFT)) this->Hitbox.recs[name].width -= value;
	else if (IsKeyDown(KEY_UP)) this->Hitbox.recs[name].height -= value;
	else if (IsKeyDown(KEY_DOWN)) this->Hitbox.recs[name].height += value;

}

void GameObject::MoveObject(unsigned int value)
{
	if (IsKeyDown(KEY_D)) this->Data.pos.x += value;
	else if (IsKeyDown(KEY_A)) this->Data.pos.x -= value;
	else if (IsKeyDown(KEY_W)) this->Data.pos.y -= value;
	else if (IsKeyDown(KEY_S)) this->Data.pos.y += value;
}

void GameObject::ResetHitbox()
{
	for (int i = 0; i < this->Hitbox.recs.size(); i++)
	{
		this->Hitbox.recs[i].x = this->Data.pos.x;
		this->Hitbox.recs[i].y = this->Data.pos.y;
		this->Hitbox.recs[i].width = this->Texture.width;
		this->Hitbox.recs[i].height = this->Texture.height;
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

Enum_WarningStatus CreateNewObject(bool& active, std::unordered_map<std::string, GameObject>& object)
{
	
	active = true;

	bool PopUpClosed = true;
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
