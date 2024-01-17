#include "GameObjects.h"

GameObject::GameObject()
{
}

GameObject::GameObject(std::string name)
{
}

void GameObject::MoveHitbox(unsigned int value, numbers name)
{
	if (IsKeyDown(KEY_D)) this->Hitbox.Data.recs[name].x += value;
	else if (IsKeyDown(KEY_A)) this->Hitbox.Data.recs[name].x -= value;
	else if (IsKeyDown(KEY_W)) this->Hitbox.Data.recs[name].y -= value;
	else if (IsKeyDown(KEY_S)) this->Hitbox.Data.recs[name].y += value;
	else if (IsKeyDown(KEY_RIGHT)) this->Hitbox.Data.recs[name].width += value;
	else if (IsKeyDown(KEY_LEFT)) this->Hitbox.Data.recs[name].width -= value;
	else if (IsKeyDown(KEY_UP)) this->Hitbox.Data.recs[name].height -= value;
	else if (IsKeyDown(KEY_DOWN)) this->Hitbox.Data.recs[name].height += value;

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
	for (int i = 0; i < this->Hitbox.Data.recs.size(); i++)
	{
		this->Hitbox.Data.recs[i].x = this->Data.pos.x;
		this->Hitbox.Data.recs[i].y = this->Data.pos.y;
		this->Hitbox.Data.recs[i].width = this->Texture.width;
		this->Hitbox.Data.recs[i].height = this->Texture.height;
	}
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
