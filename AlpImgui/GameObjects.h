#pragma once
#include <iostream>
#include "raylib.h"
#include <vector>
#include <string>
#include "Imgui/imgui.h"
#include <map>
#include "WarningHandler.h"
#include "rlgl.h"
#include "raymath.h"
#include <tuple>
#include <filesystem>



#define stringify( name ) #name
#define PRINT_VARIABLE(x) std::cout << #x"=" << x << std::endl
#define HITBOXINDEX SelectedObject->Hitbox.SelectedHitboxs.SelectedHitbox


enum numbers { first, second, third, fourth, fifth };
enum enum_SelectedShape { enum_Rectangle, enum_Triangle, enum_Circle };


std::string toString(numbers name);
static int Iterator = 1;

//enum Focus { Hitboxs, Objects, SelectedHitbox, SelectedObject };


struct Focus
{
	int Hitboxs = 0;
	int Objects = 1;
	int SelectedHitbox = 2;
	int SelectedObject = 3;


};



struct Circle
{
	numbers name;
	Vector2 origin;
	float radius;
};

struct Triangle
{
	Triangle(numbers name, Vector2 x, Vector2 y, Vector2 z)
	{
		this->name = name;
		this->v1 = x;
		this->v2 = y;
		this->v3 = z;

	}

	numbers name;

	Vector2 v1;
	Vector2 v2;
	Vector2 v3;



};


class Rectanglex
{
public:
	Rectanglex(numbers name,int x,int y, int width,int height)
	{
		this->name = name;
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}
	Rectanglex() = default;
	numbers name;
	int x;
	int y;
	int width;
	int height;

	void operator()(const Rectanglex& other)
	{
		this->name = other.name;
		this->x = other.x;
		this->y = other.y;
		this->width = other.width;
		this->height = other.height;

	}
	Rectangle ConvertRec()
	{
		Rectangle rec;
		rec.x = this->x;
		rec.y = this->y;
		rec.width = this->width;
		rec.height = this->height;
		return rec;
	}
	

};


class ObjectData
{
public:

	
	Vector2 pos;
	Vector2 OriginalTextureSize;
	float TextureScale = 1.0f;
	float rotation = 0.0f;
	
	
	
	ObjectData()
	{

	};
	

};

struct struct_SelectedHitboxs
{
	
	
	enum_SelectedShape SelectedShape;
	numbers SelectedHitbox;

};



class CollisionBoxs
{
public:

	std::vector<Rectanglex> recs;
	std::vector<Circle> circles;
	std::vector<Triangle> triangles;
	bool Locked = false;
	bool ShowAllHitboxs = true;
	struct_SelectedHitboxs SelectedHitboxs;

};



class GameObject
{
public:
	 GameObject();
	 GameObject(std::string name);
	 GameObject(char name);
	~GameObject();

	std::string ObjectName;

	ObjectData Data;
	CollisionBoxs Hitbox;
	Texture2D Texture;
	unsigned int Id = 0;
	int RenderQueue;
	int MoveValue = 1;
	bool ShouldHitboxDisplay = false;
	bool ShouldObjectOrHitboxMove = true;
	bool Locked;
	
	
	void MoveHitbox(struct_SelectedHitboxs Data, int value = 10);
	void MoveObject(unsigned int value = 10);
	void ResetHitbox();
	void UpdateTextureSize();
	void ShowHitbox(bool active = false);

	/*bool operator>(const GameObject& other) const
	{
		return this->Data.RenderQueue > other.Data.RenderQueue;
	}
	bool operator<(const GameObject& other) const
	{
		return this->Data.RenderQueue < other.Data.RenderQueue;
	}

	bool operator<=(const GameObject& other) const
	{
		return this->Data.RenderQueue <= other.Data.RenderQueue;
	}
	bool operator>=(const GameObject& other) const
	{
		return this->Data.RenderQueue >= other.Data.RenderQueue;
	}*/




};

void IncreaseRenderQueue(std::map<std::string, GameObject>& objects, GameObject*& SelectedObject);
void DecreaseRenderQueue(std::map<std::string, GameObject>& objects, GameObject*& SelectedObject);



std::vector<std::pair<std::string, std::string>> ReadMultipleFilesFromDirectory(const char* FilePathToDirectory);
std::string GetRelativePath();
void CreateNullObject(std::map<std::string, GameObject>& objects);
void DeleteNullObject(std::map<std::string, GameObject>& objects);
void DrawObjects(const std::map<std::string, GameObject>& objects,bool DrawAll = true);
void DrawHitboxs(std::map<std::string, GameObject>& objects, GameObject*& SelectedObject, bool DrawAll = false);
void SelectHitboxWithMouse(GameObject*& SelectedObject);
void SelectObjectWithMouse(std::map<std::string, GameObject>& objects, GameObject*& pointer,Vector2 CameraOffset);
void ShowRenderQueue(std::map<std::string, GameObject>& objects, GameObject*& SelectedObject,bool ShowQueue);
bool CollisionMouseWithTexture(Vector2 mouse, ObjectData object, Texture2D Texture);
bool CollisionMouseWithRec(Vector2 mouse, Rectanglex rec);
void SetPrioarity(std::map<std::string, GameObject>& objects, GameObject*& SelectedObject);
std::string  GetRelativePath(std::string TextureName);
Enum_WarningStatus CreateNewObject(bool& active, std::map<std::string, GameObject>& object);
Enum_WarningStatus DeleteSelectedObject(std::map<std::string, GameObject>& objects,GameObject*& SelectedObject, bool &active);



