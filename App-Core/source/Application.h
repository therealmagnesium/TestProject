#pragma once
#include "Base.h"
#include <string>

namespace Core
{
    struct ApplicationSpecification
    {
        std::string name = "Untitled";
        std::string version = "1.0-dev";
        std::string author = "No author specified";

        u32 windowWidth = 1280;
        u32 windowHeight = 720;

        bool isVsyncEnabled = true;
    };

    class Application
    {
    public:
        Application() = default;
        Application(ApplicationSpecification& spec);
        ~Application();

        void Run();
        void Quit();

    protected:
        virtual void OnUpdate() {};
        virtual void OnRender() {};
        virtual void OnRenderUI() {};

    private:
        bool m_isRunning = true;
        ApplicationSpecification m_specification;
    };
}

extern Core::Application App;
