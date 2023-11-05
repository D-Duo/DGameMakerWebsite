#include "WindowConsole.h"
#include "App.h"

WindowConsole::WindowConsole(string name, bool startEnabled, ImGuiWindowFlags flags) : GUI_Window(name, startEnabled, flags) {
    this->autoScroll = true;
    this->showUpdateLogs = false;
};

void CopyTextToClipboard(const std::string& text) {
    if (OpenClipboard(NULL)) {
        EmptyClipboard();
        HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, text.size() + 1);
        if (hMem) {
            char* pMem = static_cast<char*>(GlobalLock(hMem));
            if (pMem) {
                strcpy_s(pMem, text.size() + 1, text.c_str());
                GlobalUnlock(hMem);
                SetClipboardData(CF_TEXT, hMem);
            }
        }
        CloseClipboard();
    }
}

void WindowConsole::Update() {

    if (ImGui::SmallButton("Clear")) { app->logStream.str(""); }
    ImGui::SameLine();
    if (ImGui::SmallButton("Copy")) {
        std::string logText = app->logStream.str();
        CopyTextToClipboard(logText);
    }
    float buttonWidth = 200;
    float windowWidth = ImGui::GetWindowContentRegionMax().x;
    float xPos = windowWidth - buttonWidth;

    ImGui::SameLine();
    ImGui::SetCursorPosX(xPos);
    if (ImGui::Checkbox("Update Logs", &this->showUpdateLogs)) {}

    ImGui::Separator();

    textFilter.Draw("Logs Filter (\"include\", \"error\")", 180);

    ImGui::SameLine();
    ImGui::SetCursorPosX(xPos);
    if (ImGui::Checkbox("Auto Scrolling", &this->autoScroll)) {}

    ImGui::Separator();

    ImGui::BeginChild("Console Output", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

    if (ImGui::BeginPopupContextWindow())    {
        if (ImGui::Selectable("Clear")) app->logStream.str("");
        ImGui::EndPopup();
    }

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1));

    std::vector<std::string> filteredLogLines;
    std::istringstream logStream(app->logStream.str());
    std::string line;
    while (std::getline(logStream, line)) {
        if (textFilter.PassFilter(line.c_str())) {
            filteredLogLines.push_back(line);
        }
    }

    // Display filtered log lines
    for (const std::string& filteredLine : filteredLogLines) {
        ImGui::TextWrapped("%s", filteredLine.c_str());
    }

    if (autoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) { ImGui::SetScrollHereY(1.0f); }

    ImGui::PopStyleVar();
    ImGui::EndChild();
}