#include "Drone.h"
#include <math.h>

template <typename T>
constexpr const T SIGN(const T m_v) {
	return m_v > 0 ? +1.0f : (m_v < 0 ? -1.0f : 0.0f);
}

std::string GetRelativeTexturePath(std::string TextureName)
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



void Drone::setTexture(DroneStatus droneStatus)
{
	if (droneStatus == DroneStatus::driving)
	{
		currentTexture = textures.drivingTexture;
	}
	if (droneStatus == DroneStatus::flying)
	{
		currentTexture = textures.flyingTexture;
	}
}

void Drone::transform()
{
	if (IsKeyPressed(KEY_Q) && isOnGround())
	{
		data.rotation = 0;
		
		if (data.droneStatus == DroneStatus::driving)
		{
			data.droneStatus = DroneStatus::flying;
			setTexture(data.droneStatus);
		}
		else if (data.droneStatus == DroneStatus::flying)
		{
			data.droneStatus = DroneStatus::driving;
			setTexture(data.droneStatus);
		}
	}
}

bool Drone::isOnGround()
{
	if (data.pos.y + data.size.height > GROUND)
		return true;
	else
		return false;
}

void Drone::readQRcode()
{
}

void Drone::Move()
{
	if (data.droneStatus == DroneStatus::driving)
	{
		data.pos.y += data.speed.y;
		
		if (!isOnGround())
		{
			data.speed.y = 1;
			
		}
		else
		{
			data.speed.y = 0;
		}

		if (isOnGround())
		{
			if (IsKeyDown(KEY_D))
			{
				data.speed.x += 1.0f;
				
				data.speed.x = clamp(data.speed.x, 0, 2);
				batteryUpdate();
				
			}
			else if (IsKeyDown(KEY_A))
			{
				data.speed.x -= 1.0f;
				data.speed.x = clamp(data.speed.x, 0, -2);
				batteryUpdate();
			}
			else
			{
				data.speed.x = move_toward(data.speed.x, 0, 0.5f);
				
			}
			data.pos.x += data.speed.x;


		}

	}
	else if (data.droneStatus == DroneStatus::flying)
	{
		if (IsKeyDown(KEY_W))
		{
			data.speed.y -= 1.0f;
			data.speed.y = clamp(data.speed.y, 0, -2);
			batteryUpdate();
			

		}
		else if (IsKeyDown(KEY_S) && !isOnGround())
		{
			data.speed.y += 1.0f;
			
			data.speed.y = clamp(data.speed.y,0,2);
			batteryUpdate();
			
		}
		else
		{
			data.speed.y = move_toward(data.speed.y, 0, 0.5f);
		}

		if (IsKeyDown(KEY_D))
		{
			data.speed.x += 1.0f;
			data.speed.x = clamp(data.speed.x, 0, 2);
			data.rotation = 45;
		

			batteryUpdate();

			
		}
		else if (IsKeyDown(KEY_A))
		{
			data.speed.x -= 1.0f;
			data.speed.x = clamp(data.speed.x, 0, -2);
			data.rotation = 315;
			batteryUpdate();
		}
		else
		{
			data.speed.x = move_toward(data.speed.x, 0, 0.5f);
			data.rotation = 0;


		}		

		if (IsKeyDown(KEY_RIGHT))
		{
			data.rotation += 1;
			if (data.rotation > 360)
				data.rotation = 0;
		}
		if (IsKeyDown(KEY_LEFT))
		{
			data.rotation -= 1;
			if (data.rotation < 0)
				data.rotation = 360;
		}

		batteryUpdate(true);
		data.pos.x += data.speed.x;
		data.pos.y += data.speed.y;
	}

}

double move_toward(double p_from, double p_to, double p_delta)
{
	return abs(p_to - p_from) <= p_delta ? p_to : p_from + SIGN(p_to-p_from) * p_delta;
}

int clamp(float value, float min, float max)
{
	return fmin(fmax(value, min), max);
}



void Drone::batteryUpdate(bool isFlyingAndStable)
{
	if (isFlyingAndStable)
		data.batteryStatus -= 0.003f;
	else
		data.batteryStatus -= 0.005f;
}
