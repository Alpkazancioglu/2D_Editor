#pragma once
#include "raylib.h"
#include <iostream>
#include <math.h>
#define GROUND 720
#define GRAVITY 10.0f

enum class DroneStatus {driving,flying };
std::string GetRelativeTexturePath(std::string TextureName);


class Drone
{
public:
	struct Size
	{
		float width;
		float height;
	};
	struct Data
	{
		
		Vector2 pos;
		Size size;
		Vector2 speed;
		int AirSpeed;
		int GroundSpeed;
		float batteryStatus;
		DroneStatus droneStatus;
		bool IsQRcodeReaded;
		Vector2 gyroSensorValue;
		int altitude;
		int rotation;

	};
	
	struct Textures
	{
		Texture2D drivingTexture = LoadTexture(GetRelativeTexturePath("droneDriving.png").c_str());
		Texture2D flyingTexture = LoadTexture(GetRelativeTexturePath("droneFlying.png").c_str());
		

	};
	
	Data data;
	Texture2D currentTexture;
	Textures textures;
	
	

	void setTexture(DroneStatus droneStatus);
	void transform();
	bool isOnGround();
	void readQRcode();
	void Move();
	void batteryUpdate(bool isFlyingAndStable = false);

	

};
double move_toward(double p_from, double p_to, double p_delta);
int clamp(float value, float min, float max);



template<typename L>
void print(const L log)
{
	std::cout << log << '\n';
}
