#pragma once
#include "Player.h"
#include "Tilemap.h"

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
    Tilemap m_tilemap;
    Camera2D m_camera;
};
