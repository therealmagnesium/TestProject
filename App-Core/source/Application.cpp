#include "Application.h"
#include <raylib.h>

namespace Core
{
    static bool appInitialized = false;

    Application::Application(ApplicationSpecification& spec) : m_specification(spec)
    {
        if (appInitialized)
        {
            TraceLog(LOG_ERROR, "Application cannot be initialized more than once!");
            return;
        }

        InitWindow(m_specification.windowWidth, m_specification.windowHeight, m_specification.name.c_str());
        SetTargetFPS(60);
        SetExitKey(KEY_NULL);

        appInitialized = true;
    }

    Application::~Application() { CloseWindow(); }

    void Application::Run()
    {
        if (!appInitialized)
        {
            TraceLog(LOG_FATAL, "Cannot run the application because it's not initialized!");
            return;
        }

        while (m_isRunning)
        {
            m_isRunning = !WindowShouldClose();
            if (IsKeyPressed(KEY_ESCAPE))
                this->Quit();

            this->OnUpdate();

            BeginDrawing();
            {
                ClearBackground({15, 15, 25, 255});
                this->OnRender();
            }
            EndDrawing();

            this->OnRenderUI();
        }
    }

    void Application::Quit() { m_isRunning = false; }
}
