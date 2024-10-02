#pragma once
#include "Base.h"
#include "Entity.h"
#include "EntityManager.h"

#include <raylib.h>
#include <string>

using namespace Scene;

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

        static inline Application* Get() { return s_instance; }
        inline const ApplicationSpecification& GetSpecification() const { return m_specification; }
        inline u64 GetCurrentFrame() const { return m_currentFrame; }

        inline void SetPrimaryCamera(Camera2D* camera) { m_primaryCamera = camera; }
        inline std::shared_ptr<Entity> CreateEntity(const char* tag) { return m_entityManager.AddEntity(tag); }

    protected:
        virtual void OnUpdate() {}
        virtual void OnRender() {}
        virtual void OnRenderUI() {}
        virtual void OnShutdown() {}

    private:
        bool m_isRunning = true;
        u64 m_currentFrame = 0;
        ApplicationSpecification m_specification;
        EntityManager m_entityManager;
        Camera2D* m_primaryCamera = NULL;

        static Application* s_instance;
    };

    extern Application* App;
}
