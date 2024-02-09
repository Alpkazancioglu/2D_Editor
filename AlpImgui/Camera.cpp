#include "Camera.h"



void CAMERA::moveCamera(Camera2D& camera)
{
	if (IsKeyDown(KEY_LEFT_SHIFT) && IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
	{
		Vector2 delta = GetMouseDelta();
		delta = Vector2Scale(delta, -1.0f / camera.zoom);

		camera.target = Vector2Add(camera.target, delta);
	}

}

void CAMERA::Zoom(Camera2D& camera)
{
	
	float wheel = GetMouseWheelMove();
	if (wheel != 0 && IsKeyDown(KEY_LEFT_SHIFT))
	{
		
		Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);
		camera.offset = GetMousePosition();
		camera.target = mouseWorldPos;
		camera.zoom += wheel * 0.125f;
		
		if (camera.zoom < 0.125f)
			camera.zoom = 0.125f;
	}
	if(IsKeyDown(KEY_LEFT_SHIFT) && IsKeyPressed(KEY_R))
	{
		camera.zoom = 1.0f;
	}

}

Camera2D CAMERA::init()
{
	Camera2D camera;
	camera.target = { (float)GetMonitorWidth(GetCurrentMonitor()) / 2,(float)GetMonitorHeight(GetCurrentMonitor()) / 2 };
	camera.offset = { (float)GetMonitorWidth(GetCurrentMonitor()) / 2,(float)GetMonitorHeight(GetCurrentMonitor()) / 2 };
	camera.zoom = 1.0f;
	camera.rotation = 0.0f;
	
	return camera;
}
