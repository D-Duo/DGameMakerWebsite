#include "WindowSettings.h"
#include "App.h"
#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#pragma comment(lib, "assimp-vc143-mt.lib")

WindowSettings::WindowSettings(string name, bool startEnabled, ImGuiWindowFlags flags) : GUI_Window(name, startEnabled, flags) {
	if ((WIN_WIDTH == 1920) && (WIN_HEIGHT == 1080)) { selectedResolution = 0; }
	else if ((WIN_WIDTH == 1280) && (WIN_HEIGHT == 720)) { selectedResolution = 1; }
	else if ((WIN_WIDTH == 1024) && (WIN_HEIGHT == 768)) { selectedResolution = 2; }
	else if ((WIN_WIDTH == 800) && (WIN_HEIGHT == 600)) { selectedResolution = 3; }
	else { selectedResolution = 4; }

	if (WIN_FULLSCREEN == 1) { selectedWindowType = 0; }
	else if (WIN_RESIZABLE == 1) {
		selectedWindowType = 1;
		selectedResolution = 4;
	}
	else if (WIN_FULLSCREEN_DESKTOP == 1) { selectedWindowType = 2; }
	else { selectedWindowType = 3; }

	if (WIN_BORDERLESS == 1) { borderless = true; }
	else { borderless = false; }

	brightnessValue = 1.0f;
	vsync = true;
};

void WindowSettings::PreUpdate() {
    int winw = 600;
    int winh = 450;
    ImGui::SetNextWindowSize(ImVec2(winw, winh));

    int winx, winy;
    SDL_Window* mainWin = app->window->GetWindow();
    SDL_GetWindowPosition(mainWin, &winx, &winy);

    winx += (app->window->GetWindowSize().x / 2) - (winw / 2);
    winy += (app->window->GetWindowSize().y / 2) - (winh / 2);
    ImGui::SetNextWindowPos(ImVec2(winx, winy));
}

void WindowSettings::Update() {
	float customSpacing = 20.0f;

	if (ImGui::BeginTabBar("Setting Menus"))
	{
		if (ImGui::BeginTabItem("Video Settings"))
		{
			ImGui::Dummy(ImVec2(1, customSpacing));

			std::vector<std::string> resolutions = { "1920x1080", "1280x720", "1024x768", "800x600", ""};
			int previousSelectedResolution = selectedResolution;

			// Display the selection item (dropdown)
			if (ImGui::BeginCombo("Resolution", resolutions[selectedResolution].c_str())) {
				for (int i = 0; i < resolutions.size(); i++) {
					bool is_selected = (i == selectedResolution);
					if (ImGui::Selectable(resolutions[i].c_str(), is_selected)) {
						selectedResolution = i; // Update the selected resolution
					}
					if (is_selected) {
						ImGui::SetItemDefaultFocus(); // Set the initial focus to the selected item
					}
				}				
				ImGui::EndCombo();
			}

			// Check if the selection has changed
			if (selectedResolution != previousSelectedResolution) {
				// Apply the selected window type
				switch (selectedResolution)
				{
				case 0:
					SDL_SetWindowSize(app->window->GetWindow(), 1920, 1080);
					SDL_SetWindowPosition(app->window->GetWindow(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
					break;
				case 1:
					SDL_SetWindowSize(app->window->GetWindow(), 1280, 720);
					SDL_SetWindowPosition(app->window->GetWindow(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
					break;
				case 2:
					SDL_SetWindowSize(app->window->GetWindow(), 1024, 768);
					SDL_SetWindowPosition(app->window->GetWindow(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
					break;
				case 3:
					SDL_SetWindowSize(app->window->GetWindow(), 800, 600);
					SDL_SetWindowPosition(app->window->GetWindow(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
					break;
				default:
					break;
				}
				// Update the previous selection
				previousSelectedResolution = selectedResolution;
			}

			ImGui::Dummy(ImVec2(1, customSpacing));

			std::vector<std::string> windowType = { "Fullscreen", "Resizable", "Fullscreen Desktop", "Normal" };
			int previousSelectedWindowType = selectedWindowType;

			// Display the selection item (dropdown)
			if (ImGui::BeginCombo("Window Type", windowType[selectedWindowType].c_str())) {
				for (int i = 0; i < windowType.size(); i++) {
					bool is_selected = (i == selectedWindowType);
					if (ImGui::Selectable(windowType[i].c_str(), is_selected)) {
						selectedWindowType = i; // Update the selected window type
					}
					if (is_selected) {
						ImGui::SetItemDefaultFocus(); // Set the initial focus to the selected item
					}
				}
				ImGui::EndCombo();
			}

			// Check if the selection has changed
			if (selectedWindowType != previousSelectedWindowType) {
				// Apply the selected window type
				switch (selectedWindowType) {
				case 0:
					SDL_SetWindowFullscreen(app->window->GetWindow(), SDL_WINDOW_FULLSCREEN);
					SDL_SetWindowResizable(app->window->GetWindow(), SDL_FALSE);
					break;
				case 1:
					SDL_SetWindowResizable(app->window->GetWindow(), SDL_TRUE);
					SDL_SetWindowFullscreen(app->window->GetWindow(), 0);
					selectedResolution = 4;
					break;
				case 2:
					SDL_SetWindowFullscreen(app->window->GetWindow(), SDL_WINDOW_FULLSCREEN_DESKTOP);
					SDL_SetWindowResizable(app->window->GetWindow(), SDL_FALSE);
					break;
				case 3:
					SDL_SetWindowFullscreen(app->window->GetWindow(), 0);
					SDL_SetWindowResizable(app->window->GetWindow(), SDL_FALSE);
					break;
				default:
					break;
				}
				// Update the previous selection
				previousSelectedWindowType = selectedWindowType;
			}

			ImGui::Dummy(ImVec2(1, customSpacing));

			if (ImGui::Checkbox("Borderless", &this->borderless)) {
				if (this->borderless) { SDL_SetWindowBordered(app->window->GetWindow(), SDL_FALSE); }
				else if (!this->borderless) { SDL_SetWindowBordered(app->window->GetWindow(), SDL_TRUE); }
			}

			ImGui::Dummy(ImVec2(1, customSpacing));
			
			float minValue = 0.0f;       // Minimum value for the slider
			float maxValue = 1.0f;     // Maximum value for the slider
			if (ImGui::SliderFloat("Brightness", &brightnessValue, minValue, maxValue)) {
				SDL_SetWindowBrightness(app->window->GetWindow(), brightnessValue);
			}

			ImGui::Dummy(ImVec2(1, customSpacing));

			ImGui::Separator();

			ImGui::Dummy(ImVec2(1, customSpacing));

			char targetFPS[50];
			if (framerate < 240) {
				sprintf_s(targetFPS, 50, "Target FPS: %d", framerate);
			}
			else {
				sprintf_s(targetFPS, 50, "Target FPS: %s", "Unlimited");
			}

			ImGui::SliderInt(" ", &framerate, 15, 241, targetFPS);

			if (framerate < 240) {
				app->ChangeFramerate(framerate);
				app->framerateUnlimited = false;
			}
			else { app->framerateUnlimited = true; }

			ImGui::SameLine();

			if (ImGui::Checkbox("VSync", &vsync)) {
				if (vsync) {
					SDL_GL_SetSwapInterval(1);
				}
				else {
					SDL_GL_SetSwapInterval(0);
				}
			}

			ImGui::Dummy(ImVec2(1, customSpacing));

			ut_history.push_back((app->updateTime) * 1000.0f);
			if (ut_history.size() > 100)
			{
				ut_history.erase(ut_history.begin());
			}

			char title[50];
			sprintf_s(title, 50, "Current Update time: %.2f", ((app->updateTime) * 1000.0f));
			ImGui::PlotHistogram("Last update duration in ms", &ut_history[0], ut_history.size(), 0, title, 0.0f, 40.0f, ImVec2(310, 100));

			ft_history.push_back((app->frameTime) * 1000.0f);
			if (ft_history.size() > 100)
			{
				ft_history.erase(ft_history.begin());
			}

			sprintf_s(title, 50, "Current Frame time: %.2f", ((app->frameTime) * 1000.0f));
			ImGui::PlotHistogram("Last frame duration in ms", &ft_history[0], ft_history.size(), 0, title, 0.0f, 40.0f, ImVec2(310, 100));

			fps_history.push_back(app->currentFPS);
			if (fps_history.size() > 100)
			{
				fps_history.erase(fps_history.begin());
			}

			sprintf_s(title, 50, "Current Framerate: %.0f", app->currentFPS);
			ImGui::PlotHistogram("Framerate", &fps_history[0], fps_history.size(), 0, title, 0.0f, 240.0f, ImVec2(310, 100));
			
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Controls"))
		{


			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Renderer")) {

		}

		if (ImGui::BeginTabItem("System Details"))
		{
			ImGui::BulletText("SDL Version: ");
			SDL_version SdlVer;
			SDL_GetVersion(&SdlVer);
			ImGui::SameLine();
			ImGui::Text("%d.%d.%d", SdlVer.major, SdlVer.minor, SdlVer.patch);

			ImGui::BulletText("DevIL Version: ");
			ILint ilVersion = ilGetInteger(IL_VERSION_NUM);
			ImGui::SameLine();
			ImGui::Text("%d.%d.%d", ilVersion / 1000, (ilVersion / 100) % 10, ilVersion % 100);

			ImGui::BulletText("ImGui Version: ");
			ImGui::SameLine();
			int major = IMGUI_VERSION_NUM / 10000;
			int minor = (IMGUI_VERSION_NUM / 100) % 100;
			ImGui::Text("%d.%d", major, minor);

			ImGui::BulletText("GLEW Version: ");
			ImGui::SameLine();
			const char* glewVersion = (const char*)glewGetString(GLEW_VERSION);
			ImGui::Text("%s", glewVersion);

			//const aiScene* _scene; // Assuming you have a valid aiScene pointer			//
			//int major = aiGetVersionMajor();												//
			//int minor = aiGetVersionMinor();												//	ASSIMP
			//int revision = aiGetVersionRevision();										//
			//ImGui::BulletText("Assimp Version: %d.%d.%d", major, minor, revision);		//

			ImGui::BulletText("Grafical controllers Version: ");			
			ImGui::SameLine();
			ImGui::Text("%s", glGetString(GL_VERSION));

			ImGui::BulletText("Grafical controllers Vendor: ");
			ImGui::SameLine();
			ImGui::Text("%s", glGetString(GL_VENDOR));

			ImGui::Separator();

			ImGui::BulletText("CPU Cores: ");
			ImGui::SameLine();
			ImGui::Text("%d", SDL_GetCPUCount());

			ImGui::BulletText("GPU: ");
			ImGui::SameLine();
			ImGui::Text("%s", glGetString(GL_RENDERER));

			ImGui::Dummy(ImVec2(1, customSpacing));

			ImGui::BulletText("RAM: ");
			ImGui::SameLine();
			ImGui::Text("%.6f GB", (((float)SDL_GetSystemRAM()) / 1000.0f));

			ImGui::Dummy(ImVec2(1, customSpacing));

			int temp;
			glGetIntegerv(GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX, &temp);
			ImGui::BulletText("VRAM Budget: ");
			ImGui::SameLine();
			ImGui::Text("%.6f GB", (((float)temp) / 1000000));

			glGetIntegerv(GL_GPU_MEMORY_INFO_EVICTION_COUNT_NVX, &temp);
			ImGui::BulletText("VRAM Used: ");
			ImGui::SameLine();
			ImGui::Text("%.6f GB", (((float)temp) / 1000000));

			glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &temp);
			ImGui::BulletText("VRAM Avilable: ");
			ImGui::SameLine();
			ImGui::Text("%.6f GB", (((float)temp) / 1000000));

			ImGui::EndTabItem();
		}

		ImGui::EndTabBar();
	}
}