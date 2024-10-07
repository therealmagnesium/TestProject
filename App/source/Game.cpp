#include "Game.h"

#include <Application.h>
#include <Animation.h>
#include <Entity.h>
#include <EntityManager.h>

#include <raylib.h>

using namespace Core;
using namespace Scene;

Game::Game(ApplicationSpecification& spec) : Application(spec)
{
    const ApplicationSpecification& appInfo = this->GetSpecification();

    m_camera.target = {0.f, 0.f};
    m_camera.offset = {0.f, 0.f};
    m_camera.zoom = 1.f;
    m_camera.rotation = 0.f;
    this->SetPrimaryCamera(&m_camera);

    m_player = CreatePlayer();
}

void Game::OnUpdate()
{
    m_player.Update();
}

void Game::OnRender()
{
}
void Game::OnRenderUI()
{
    const char* message = TextFormat("Is Grounded: %d", m_player.isGrounded);
    DrawText(message, 20, 20, 48, YELLOW);
}

void Game::OnShutdown()
{
    FreePlayer(m_player);
}
