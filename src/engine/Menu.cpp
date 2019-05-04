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

void menuDynamic(bool &buttonRun) {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	bool run = true;

	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoTitleBar;
	window_flags |= ImGuiWindowFlags_NoCollapse;
	window_flags |= ImGuiWindowFlags_NoScrollbar;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoBackground;
	ImGui::SetNextWindowPos(ImVec2(20, 20));
	ImGui::SetNextWindowSize(ImVec2(450, 60));
	{
		ImGui::Begin("TEST", &run, window_flags);
		ImGui::SetWindowFontScale(1.0f);
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "TEST: %d", 0.5f);
		ImGui::End();
	}


	ImGui::SetNextWindowPos(ImVec2(435, 100));
	ImGui::SetNextWindowSize(ImVec2(410, 520));
	{
		ImGui::Begin("Menu", &buttonRun, window_flags);

		ImGui::Button("Button", ImVec2(100, 100)); 
		if (ImGui::IsItemActivated())
			buttonRun = false;

		ImGui::End();
	}
}