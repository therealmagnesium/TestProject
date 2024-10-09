#include "Game.h"

#include <Application.h>
#include <Animation.h>
#include <Entity.h>
#include <EntityManager.h>
#include <Tilemap.h>

#include <raylib.h>

using namespace Core;
using namespace Scene;

Game::Game(ApplicationSpecification& spec) : Application(spec)
{
    const ApplicationSpecification& appInfo = this->GetSpecification();

    m_camera.target = {0.f, 0.f};
    m_camera.offset = {appInfo.windowWidth / 2.f, appInfo.windowHeight / 2.f};
    m_camera.zoom = 1.f;
    m_camera.rotation = 0.f;
    this->SetPrimaryCamera(&m_camera);

    m_player = CreatePlayer();
    m_tilemap = LoadTilemap("assets/Test.tmx");
}

void Game::OnUpdate()
{
    const ApplicationSpecification& appInfo = this->GetSpecification();
    m_player.Update();

    m_camera.target = m_player.GetTransform().position;
}

void Game::OnRender()
{
    DrawTilemap(m_tilemap);
}
void Game::OnRenderUI()
{
    // const char* message = TextFormat("Player Y: %.3f", m_player.GetTransform().position.y);
    // DrawText(message, 20, 20, 48, YELLOW);
}

void Game::OnShutdown()
{
    FreePlayer(m_player);
    FreeTilemap(m_tilemap);
}
