#include "Application.h"
#include <raylib.h>

namespace Core
{
    static bool appInitialized = false;
    Application* Application::s_instance = NULL;
    Application* App;

    Application::Application(ApplicationSpecification& spec) : m_specification(spec)
    {
        if (appInitialized)
        {
            TraceLog(LOG_ERROR, "Application cannot be initialized more than once!");
            return;
        }

        App = s_instance = this;

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
            this->Quit();
            return;
        }

        if (!m_primaryCamera)
        {
            TraceLog(LOG_FATAL, "Cannot run the application because no primary camera is set!");
            this->Quit();
            return;
        }

        while (m_isRunning)
        {
            m_currentFrame++;

            m_isRunning = !WindowShouldClose();
            if (IsKeyPressed(KEY_ESCAPE))
                this->Quit();

            m_entityManager.Update();
            this->OnUpdate();

            BeginDrawing();
            {
                BeginMode2D(*m_primaryCamera);
                {
                    ClearBackground({15, 15, 25, 255});
                    m_entityManager.DrawEntities();
                    this->OnRender();
                }
                EndMode2D();

                this->OnRenderUI();
            }
            EndDrawing();
        }

        this->OnShutdown();
    }

    void Application::Quit() { m_isRunning = false; }
}
