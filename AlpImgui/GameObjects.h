#pragma once
#include <iostream>
#include "raylib.h"
#include <vector>
#include <string>
#include "Imgui/imgui.h"
#include <unordered_map>
#include "imguistyle.h"
#include "WarningHandler.h"
#define stringify( name ) #name

enum numbers {first,second,third,fourth,fifth};

const char* toString(numbers name);

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
	numbers name;
	Vector3 positions;
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
	

	
	ObjectData()
	{

	}

};

class CollisionBoxs
{
public:

	std::vector<Rectanglex> recs;
	std::vector<Circle> circles;
	std::vector<Triangle> triangles;
	bool ShowAllHitboxs = true;

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
	
	bool ShouldHitboxDisplay = false;
	void MoveHitbox(unsigned int value = 10,numbers name = first);
	void MoveObject(unsigned int value = 10);
	void ResetHitbox();
	
	void ShowHitbox(bool active = false);






};
std::string  GetRelativePath(std::string TextureName);
Enum_WarningStatus CreateNewObject(bool& active, std::unordered_map<std::string, GameObject>& object);


