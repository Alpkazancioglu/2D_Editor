#include "ImguiStyle.h"

void ImGui::InfoMenu(Drone drone)
{
	ImGui::SetNextWindowPos({0,0});
	if (ImGui::Begin("GeneralMenu", (bool*)0, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize))
	{
		std::string droneString;
		if (drone.data.droneStatus == DroneStatus::driving)
		{
			droneString = "drivingMode";
		}
		else
		{
			droneString = "FlyingMode";
		}
		
		ImGui::Text( "mode : %s",droneString);
		ImGui::PushItemWidth(40);
		ImGui::InputFloat("speed.x", &drone.data.speed.x, 0.0f, 0.0f, "%2f", ImGuiInputTextFlags_ReadOnly);
		ImGui::SameLine();
		ImGui::InputFloat("speed.y", &drone.data.speed.y, 0.0f, 0.0f, "%2f", ImGuiInputTextFlags_ReadOnly);
		ImGui::InputInt("rotation", &drone.data.rotation, 0,0, ImGuiInputTextFlags_ReadOnly);
		ImGui::Text("BatteryStatus");
		ImGui::SameLine();
		ImGui::ProgressBar(0.01*drone.data.batteryStatus);
		
		ImGui::PopItemWidth();
		ImGui::End();
	}
}
