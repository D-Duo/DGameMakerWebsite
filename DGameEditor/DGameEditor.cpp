#include "EditorGlobals.h"
#include "ModuleGL.h"
#include "ModuleWindow.h"
#include "ModuleEvents.h"
#include "ModuleGUI.h"

using namespace chrono;

ModuleGUI* moduleGui = new ModuleGUI();

static const unsigned int FPS = 60;
static const auto FDT = 1.0s / FPS;

int main(int argc, char* argv[])
{
    try {

        auto window = ModuleWindow::SDLWindowInit();
        auto gl_context = ModuleGL::CreateWindowContext(window);
        ModuleGL::OpenGLInit();

        GameEngine engine;
        engine.camera.fov = 60;
        engine.camera.aspect = static_cast<double>(WIN_WIDTH) / WIN_HEIGHT;
        engine.camera.zNear = 0.1;
        engine.camera.zFar = 100;
        engine.camera.eye = vec3(5, 1.75, 5);
        engine.camera.center = vec3(0, 1, 0);
        engine.camera.up = vec3(0, 1, 0);

        moduleGui->ImguiInit(window, gl_context);

        while (ModuleEvents::SDLEventsProcess()) {
            const auto frame_start = steady_clock::now();
            engine.step(FDT);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
            

            //IMGUI

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplSDL2_NewFrame();
            ImGui::NewFrame();
            ImGui::ShowDemoWindow(); // Show demo window! :)
            moduleGui->ImguiExample();
            glClearColor(moduleGui->clear_color.x * moduleGui->clear_color.w, moduleGui->clear_color.y * moduleGui->clear_color.w, moduleGui->clear_color.z * moduleGui->clear_color.w, moduleGui->clear_color.w);


            ImGui::Render();

            engine.render(GameEngine::RenderModes::DEBUG); //engine render

            //glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT); //Change opgl window size
           
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            SDL_GL_SwapWindow(window);
            

            const auto frame_end = steady_clock::now();
            const auto frame_duration = frame_end - frame_start;
            if (frame_duration < FDT) this_thread::sleep_for(FDT - frame_duration);
        }

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();

        SDL_GL_DeleteContext(gl_context);
        SDL_DestroyWindow(window);
        SDL_Quit();

        return EXIT_SUCCESS;
    }
    catch(const exception& ex) {
        cerr << ex.what() << endl;
        return EXIT_FAILURE;
    }
}