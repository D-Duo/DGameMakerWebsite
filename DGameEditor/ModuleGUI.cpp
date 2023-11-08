#include "ModuleGUI.h"
#include "App.h"

#include "GUI_MenuBar.h"

ModuleGUI::ModuleGUI(bool startEnabled) : Module(startEnabled)
{
	name = "GUI";

	// Create the windows
	w_scene = new WindowScene("Scene", false);
	w_hierarchy = new WindowHierarchy("Hierarchy", true);
	w_inspector = new WindowInspector("Inspector", true);
	w_project = new WindowProject("Project", true);
	w_console = new WindowConsole("Console", true);
	w_settings = new WindowSettings("Settings", false, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysVerticalScrollbar);
	w_about = new WindowAbout("About this engine...", false, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysVerticalScrollbar);

	// Add the windows to the queue
	AddWindow(w_scene);
	AddWindow(w_hierarchy);
	AddWindow(w_inspector);
	AddWindow(w_project);
	AddWindow(w_console);
	AddWindow(w_settings);
	AddWindow(w_about);
}

ModuleGUI::~ModuleGUI() {

}

void ModuleGUI::AddWindow(GUI_Window* window) {
	this->windows.push_back(window);
}

void ModuleGUI::Awake() {
	w_scene->SceneFBO.Create_FrameBuffer(app->window->GetWindowSize().x, app->window->GetWindowSize().y);
	this->ImguiInit(app->window->GetWindow(), app->window->GetContext());
}

void ModuleGUI::Start() {
	this->w_settings->framerate = app->GetFrameRate();
}

bool ModuleGUI::PreUpdate() {
	bool ret = true;

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	ret = this->ImguiDockspace();

	return ret;
}

bool ModuleGUI::Update(std::chrono::duration<double> dt) {
	bool ret = true;
	this->ImguiSetup();

	return ret;
}

bool ModuleGUI::PostUpdate() {
	ImGuiIO& io = ImGui::GetIO();

	glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);

	io.DisplaySize = ImVec2(app->window->GetWindowSize().x, app->window->GetWindowSize().y);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		app->window->UpdateWindowContext(app->window->GetWindow(), app->window->GetContext());
	}

	return true;
}

void ModuleGUI::CleanUp() {

	this->windows.clear();

	// Cleanup ImGui
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

void ModuleGUI::ImguiInit(SDL_Window *window, SDL_GLContext gl_context){
	// Initialize ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable window DockSpaces
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;		  // Enable multiple Viewports
	font1_body_12 = io.Fonts->AddFontFromFileTTF("Assets/Fonts/font_1.ttf", 12);  // Add custom font
	font1_body_14 = io.Fonts->AddFontFromFileTTF("Assets/Fonts/font_1.ttf", 14);  // Add custom font
	io.FontDefault = io.Fonts->Fonts.back();									  // Set this font as the default one
	font1_title_18 = io.Fonts->AddFontFromFileTTF("Assets/Fonts/font_1.ttf", 18);  // Add custom font
	font_awesome_title = io.Fonts->AddFontFromFileTTF("Assets/Fonts/font_awesome.ttf", 20);  // Add custom font

	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	// Setup ImGui for SDL and OpenGL3
	ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
	ImGui_ImplOpenGL3_Init("#version 330 core");

	// Set up ImGui style (optional)
	//ImGui::StyleColorsDark();

#pragma region Imgui color pallete

	style.Colors[ImGuiCol_BorderShadow] =			ImVec4(0.0f, 0.0f, 0.0f, 0.0f);

	style.Colors[ImGuiCol_MenuBarBg] =				ImVec4(0.10f, 0.12f, 0.17f, 1.0f);

	style.Colors[ImGuiCol_TabActive] =				ImVec4(0.09f, 0.15f, 0.16f, 1.0f);
	style.Colors[ImGuiCol_TabHovered] =				ImVec4(0.09f, 0.15f, 0.16f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrab] =			ImVec4(0.09f, 0.15f, 0.16f, 1.0f);
	style.Colors[ImGuiCol_TabUnfocusedActive] =		ImVec4(0.09f, 0.15f, 0.16f, 1.0f);
	style.Colors[ImGuiCol_TabUnfocused] =			ImVec4(0.09f, 0.15f, 0.16f, 0.7f);
	style.Colors[ImGuiCol_Tab] =					ImVec4(0.09f, 0.15f, 0.16f, 0.7f);

	style.Colors[ImGuiCol_ResizeGrip] =				ImVec4(0.47f, 0.77f, 0.83f, 0.04f);
	style.Colors[ImGuiCol_SliderGrab] =				ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
	style.Colors[ImGuiCol_Button] =					ImVec4(0.47f, 0.77f, 0.83f, 0.14f);

	
	style.Colors[ImGuiCol_Header] =					ImVec4(0.1529f, 0.3882f, 0.5490f, 1.0f);	
	style.Colors[ImGuiCol_TitleBgActive] =			ImVec4(0.1529f, 0.3882f, 0.5490f, 1.0f);

	style.Colors[ImGuiCol_TextSelectedBg] =			ImVec4(0.176f, 0.631f, 0.929f, 0.43f);
	style.Colors[ImGuiCol_ResizeGripHovered] =		ImVec4(0.176f, 0.631f, 0.929f, 0.78f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] =	ImVec4(0.176f, 0.631f, 0.929f, 0.78f);
	style.Colors[ImGuiCol_SeparatorHovered] =		ImVec4(0.176f, 0.631f, 0.929f, 0.78f);
	style.Colors[ImGuiCol_FrameBgHovered] =			ImVec4(0.176f, 0.631f, 0.929f, 0.78f);
	style.Colors[ImGuiCol_ButtonHovered] =			ImVec4(0.176f, 0.631f, 0.929f, 0.86f);
	style.Colors[ImGuiCol_HeaderHovered] =			ImVec4(0.176f, 0.631f, 0.929f, 0.86f);
	style.Colors[ImGuiCol_SliderGrabActive] =		ImVec4(0.176f, 0.631f, 0.929f, 0.86f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] =	ImVec4(0.176f, 0.631f, 0.929f, 0.86f);
	style.Colors[ImGuiCol_ResizeGripActive] =		ImVec4(0.176f, 0.631f, 0.929f, 0.86f);
	style.Colors[ImGuiCol_PlotLinesHovered] =		ImVec4(0.176f, 0.631f, 0.929f, 0.86f);
	style.Colors[ImGuiCol_PlotHistogramHovered] =	ImVec4(0.176f, 0.631f, 0.929f, 0.86f);
	style.Colors[ImGuiCol_SeparatorActive] =		ImVec4(0.176f, 0.631f, 0.929f, 0.86f);
	style.Colors[ImGuiCol_FrameBgActive] =			ImVec4(0.176f, 0.631f, 0.929f, 0.86f);
	style.Colors[ImGuiCol_ButtonActive] =			ImVec4(0.176f, 0.631f, 0.929f, 0.86f);
	style.Colors[ImGuiCol_HeaderActive] =			ImVec4(0.176f, 0.631f, 0.929f, 0.86f);

	style.Colors[ImGuiCol_WindowBg] =				ImVec4(0.13f, 0.14f, 0.17f, 1.0f);

	style.Colors[ImGuiCol_Border] =					ImVec4(0.2353f, 0.2706f, 0.3451f, 1.0f);
	style.Colors[ImGuiCol_TitleBg] =				ImVec4(0.2353f, 0.2706f, 0.3451f, 1.0f);
	style.Colors[ImGuiCol_TitleBgCollapsed] =		ImVec4(0.2353f, 0.2706f, 0.3451f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarBg] =			ImVec4(0.2353f, 0.2706f, 0.3451f, 1.0f);
	style.Colors[ImGuiCol_FrameBg] =				ImVec4(0.2353f, 0.2706f, 0.3451f, 1.0f);

	style.Colors[ImGuiCol_Separator] =				ImVec4(0.3922f, 0.3922f, 0.3922f, 1.0f);
			
	style.Colors[ImGuiCol_PlotLines] =				ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
	style.Colors[ImGuiCol_PlotHistogram] =			ImVec4(0.86f, 0.93f, 0.89f, 0.63f);

	style.Colors[ImGuiCol_CheckMark] =				ImVec4(1.0f, 1.0f, 1.0f, 0.78f);
		
	style.Colors[ImGuiCol_PopupBg] =				ImVec4(0.20f, 0.22f, 0.27f, 0.9f);
	

#pragma endregion

	style.WindowMinSize = ImVec2(100, 20);
	style.GrabMinSize = 8.0f;
	style.WindowRounding = 1.5f;
	style.FrameRounding = 1.5f;
	style.GrabRounding = 1.5f;
	style.Alpha = 1.0f;

	customStyle1 = SaveImGuiStyle();
}

bool ModuleGUI::ImguiDockspace() {
	bool ret = true;

	// Enable docking (if not already enabled by default)
	ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

	// Create a main dockspace
	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
	{
		window_flags |= ImGuiWindowFlags_NoBackground;
	}

	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	if (!ImGui::Begin("MyDockSpace", NULL, window_flags)) throw exception("ImGui Window Begin returned false (Error on creating the Imgui Window)");
	ImGui::PopStyleVar(3);

	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

		static auto deployed = false;  // Only done in the first dockspace setup (no Update needed)
		if (!deployed) {
			deployed = true;

			ImGui::DockBuilderRemoveNode(dockspace_id); // clear previous layouts
			ImGui::DockBuilderAddNode(dockspace_id, dockspace_flags | ImGuiDockNodeFlags_DockSpace);
			ImGui::DockBuilderSetNodeSize(dockspace_id, viewport->Size);

			ImGui::DockBuilderDockWindow("Scene", dockspace_id);
			ImGui::DockBuilderDockWindow("Inspector", ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Right, 0.2f, nullptr, &dockspace_id));
			auto dock_down = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Down, 0.3f, nullptr, &dockspace_id);
			ImGui::DockBuilderDockWindow("Project", dock_down);
			ImGui::DockBuilderDockWindow("Console", dock_down);
			ImGui::DockBuilderDockWindow("Hierarchy", ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Left, 0.25f, nullptr, &dockspace_id));
			ImGui::DockBuilderFinish(dockspace_id);
		}
	}

	ret = MenuBarUpdate();

	ImGui::End();

	RestoreImGuiStyle(customStyle1);

	return ret;
}

void ModuleGUI::ImguiSetup() {
	for (const auto& item : windows)
	{
		if (item->GetWindowState() == States::DISABLED)
			continue;

		item->UpdateWindow();
	}
}