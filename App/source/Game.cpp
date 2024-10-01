#include "Game.h"
#include <Application.h>
#include <Entity.h>
#include <EntityManager.h>
#include <raylib.h>

using namespace Core;
using namespace Scene;

std::shared_ptr<Entity> entity;

Game::Game(ApplicationSpecification& spec) : Application(spec)
{
    const ApplicationSpecification& appInfo = this->GetSpecification();

    m_camera.target = {0.f, 0.f};
    m_camera.offset = {0.f, 0.f};
    m_camera.zoom = 1.f;
    m_camera.rotation = 0.f;
    this->SetPrimaryCamera(&m_camera);

    entity = this->CreateEntity("Entity");
    entity->AddComponent<TransformComponent>();
    entity->AddComponent<SpriteRendererComponent>("assets/textures/texel_checker.png");
}

void Game::OnUpdate() {}

void Game::OnRender() {}
