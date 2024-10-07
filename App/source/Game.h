#pragma once
#include "Player.h"

#include <Application.h>
#include <raylib.h>

using namespace Core;

class Game : public Application
{
public:
    Game(ApplicationSpecification& spec);

    void OnUpdate() override;
    void OnRender() override;
    void OnRenderUI() override;
    void OnShutdown() override;

private:
    Player m_player;
    Camera2D m_camera;
};
