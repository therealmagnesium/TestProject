#include "Game.h"

#include <Application.h>
#include <Animation.h>
#include <Entity.h>
#include <EntityManager.h>

#include <raylib.h>

using namespace Core;
using namespace Scene;

std::shared_ptr<Entity> entity;
static Texture2D tex;
static Animation anim;

Game::Game(ApplicationSpecification& spec) : Application(spec)
{
    const ApplicationSpecification& appInfo = this->GetSpecification();

    m_camera.target = {0.f, 0.f};
    m_camera.offset = {0.f, 0.f};
    m_camera.zoom = 1.f;
    m_camera.rotation = 0.f;
    this->SetPrimaryCamera(&m_camera);

    tex = LoadTexture("assets/textures/sunnyland/Packs/Sunnyland/spritesheets/player.png");
    anim = Animation(10, 4, {tex.width / 6.f, tex.height / 11.f});
    anim.Play();

    entity = this->CreateEntity("Entity");
    auto& tc = entity->AddComponent<TransformComponent>((Vector2){100.f, 100.f}, 0.f, (Vector2){4.f, 4.f});
    auto& src = entity->AddComponent<SpriteRendererComponent>(&tex);
}

void Game::OnUpdate()
{
    auto& src = entity->GetComponent<SpriteRendererComponent>();
    anim.Update();
    src.source = anim.GetSource();
}

void Game::OnRender() {}

void Game::OnShutdown() { UnloadTexture(tex); }
