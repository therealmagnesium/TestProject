#pragma once
#include <Application.h>
#include <raylib.h>

using namespace Core;

class Game : public Application
{
public:
    Game(ApplicationSpecification& spec);

    void OnUpdate() override;

private:
    Camera2D m_camera;
};
