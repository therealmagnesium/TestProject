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
static Animation anims[5];

Game::Game(ApplicationSpecification& spec) : Application(spec)
{
    const ApplicationSpecification& appInfo = this->GetSpecification();

    m_camera.target = {0.f, 0.f};
    m_camera.offset = {0.f, 0.f};
    m_camera.zoom = 1.f;
    m_camera.rotation = 0.f;
    this->SetPrimaryCamera(&m_camera);

    tex = LoadTexture("assets/textures/sunnyland/Packs/Sunnyland/spritesheets/player.png");
    anims[0] = Animation(10, 4, 0, 11, 6, 0, tex);
    anims[1] = Animation(10, 6, 0, 11, 6, 1, tex);
    anims[2] = Animation(6, 3, 0, 12, 6, 3, tex);

    entity = this->CreateEntity("Entity");
    entity->AddComponent<TransformComponent>((Vector2){100.f, 100.f}, 0.f, (Vector2){4.f, 4.f});
    entity->AddComponent<SpriteRendererComponent>(&tex);
    auto& ac = entity->AddComponent<AnimatorComponent>(anims, 5);
    ac.SetAnimationIndex(1);
    ac.Play();
}

void Game::OnUpdate() {}

void Game::OnRender() {}

void Game::OnShutdown() { UnloadTexture(tex); }
