#pragma once
#include "GUI_Window.h"

#include <filesystem>

namespace fs = std::filesystem;
struct SDL_Surface;

class WindowProject : public GUI_Window
{
public:
	WindowProject(string name, bool startEnabled = false, ImGuiWindowFlags flags = ImGuiWindowFlags_None);

	void Update();

	//Column 1
	void ShowLibraryTree(const fs::path& rootDirectory, int counter, ImGuiTreeNodeFlags bFlags);

	//Column 2
	void ShowLibraryFiles(fs::path& sPath, int numFiles);

	bool HasFilesInDirectory(const fs::path& directoryPath);
	bool IsLibrary(const fs::path& directoryPath);
	int GetNumFiles(const fs::path& directoryPath);
	SDL_Texture* LoadTextureFromFile(const fs::path& textPath);

private:
	int selected = 0;
	int counter = 0;
	const fs::path directoryPath = "Assets//";
	fs::path selectedPath;

	int minTreeColumnWidth = 150;

	SDL_Texture* imageIcon;
	SDL_Texture* fontIcon;
	SDL_Texture* fbxIcon;
	SDL_Texture* comingSoonIcon;
	SDL_Texture* folderIcon;
};