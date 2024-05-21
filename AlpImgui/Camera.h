#pragma once
#include <raylib.h>
#include <iostream>
#include <raymath.h>



namespace CAMERA
{
	void moveCamera(Camera2D& camera);
	void Zoom(Camera2D& camera);
	Camera2D init();

}
