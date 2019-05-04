#include "Menu.h"

void menuStatic(GLFWwindow& window) {
	const char* glsl_version = "#version 330";

	// IMGUI static
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplGlfw_InitForOpenGL(&window, true);
	ImGui::StyleColorsDark();
	ImGui_ImplOpenGL3_Init(glsl_version);
}

ImGuiWindowFlags runFlags() {
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoTitleBar;
	window_flags |= ImGuiWindowFlags_NoCollapse;
	window_flags |= ImGuiWindowFlags_NoScrollbar;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoBackground;

	return window_flags;
}

// All dynamic imGui code
void menuDynamic() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	bool run = true;
	extern bool moving[6];
	ImGuiWindowFlags window_flags = runFlags();

	// left
	ImGui::SetNextWindowPos(ImVec2(PADDING, PADDING));
	ImGui::SetNextWindowSize(ImVec2(BUTTON_SIZE, BUTTON_SIZE));
	{
		ImGui::Begin("ButtonsLeft", &run, window_flags);

		ImGui::Button("-x", ImVec2(BUTTON_SIZE, BUTTON_SIZE));
		if (ImGui::IsItemActivated()) moving[0] = true;

		ImGui::End();
	}

	// right
	ImGui::SetNextWindowPos(ImVec2(BUTTON_SIZE + PADDING, PADDING));
	ImGui::SetNextWindowSize(ImVec2(BUTTON_SIZE, BUTTON_SIZE));
	{
		ImGui::Begin("ButtonRight", &run, window_flags);

		ImGui::Button("x", ImVec2(BUTTON_SIZE, BUTTON_SIZE));
		if (ImGui::IsItemActivated()) moving[1] = true;

		ImGui::End();
	}

	//forward/backward
	ImGui::SetNextWindowPos(ImVec2(PADDING, BUTTON_SIZE + PADDING));
	ImGui::SetNextWindowSize(ImVec2(BUTTON_SIZE, BUTTON_SIZE * 2));
	{
		ImGui::Begin("ButtonsForwardBackward", &run, window_flags);

		ImGui::Button("z", ImVec2(BUTTON_SIZE, BUTTON_SIZE));
		if (ImGui::IsItemActivated()) moving[2] = true;

		ImGui::Button("-z", ImVec2(BUTTON_SIZE, BUTTON_SIZE));
		if (ImGui::IsItemActivated()) moving[3] = true;

		ImGui::End();
	}

	// up/down
	ImGui::SetNextWindowPos(ImVec2(BUTTON_SIZE + PADDING, BUTTON_SIZE + PADDING));
	ImGui::SetNextWindowSize(ImVec2(BUTTON_SIZE, BUTTON_SIZE * 2));
	{
		ImGui::Begin("ButtonsUpDown", &run, window_flags);

		ImGui::Button("y(up)", ImVec2(BUTTON_SIZE, BUTTON_SIZE));
		if (ImGui::IsItemActivated()) moving[4] = true;

		ImGui::Button("y(down)", ImVec2(BUTTON_SIZE, BUTTON_SIZE));
		if (ImGui::IsItemActivated()) moving[5] = true;

		ImGui::End();
	}
}

void updateCords(glm::vec3& CameraCordsOffset) {
	extern bool moving[6];
	
	// is in an if else since only one can be true at a time and valeus ais in an array
	if (moving[0]) {
		
	}
	else if (moving[1]) {

	}
	else if (moving[2]) {

	}
	else if (moving[3]) {
	
	}
	else if (moving[4]) {

	}
	else if (moving[5]) {

	}

	// Display cords
	ImGuiWindowFlags window_flags = runFlags();
	ImGui::SetNextWindowPos(ImVec2(BUTTON_SIZE + PADDING, PADDING));
	ImGui::SetNextWindowSize(ImVec2(450, 60));
	{
		ImGui::Begin("ButtonsUpDown", nullptr, window_flags);

		ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "Coordinates x: %d, y: %d, z: %d", CameraCordsOffset.x, CameraCordsOffset.y, CameraCordsOffset.z);

		ImGui::End();
	}

}