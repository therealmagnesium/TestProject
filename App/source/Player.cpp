#include "Player.h"

#include <Application.h>
#include <raylib.h>

using namespace Core;

Player CreatePlayer()
{
    Player player;

    player.texture = new Texture2D;
    *player.texture = LoadTexture("assets/textures/sunnyland/Packs/Sunnyland/spritesheets/player.png");
    player.animations[ANIM_PLAYER_IDLE] = Animation(10, 4, 0, 11, 6, 0, *player.texture);
    player.animations[ANIM_PLAYER_WALK] = Animation(12, 6, 0, 11, 6, 1, *player.texture);
    player.animations[ANIM_PLAYER_CROUCH] = Animation(6, 3, 0, 12, 6, 3, *player.texture);

    player.entity = App->CreateEntity("Player");
    player.entity->AddComponent<TransformComponent>((Vector2){100.f, 100.f}, 0.f, (Vector2){4.f, 4.f});
    player.entity->AddComponent<SpriteRendererComponent>(player.texture);
    player.entity->AddComponent<AnimatorComponent>(player.animations, ANIM_PLAYER_COUNT).Play();

    return player;
}

void FreePlayer(Player& player)
{
    UnloadTexture(*player.texture);
    delete player.texture;
    player.texture = NULL;
}

void Player::Update()
{
    auto& tc = entity->GetComponent<TransformComponent>();
    auto& src = entity->GetComponent<SpriteRendererComponent>();
    auto& ac = entity->GetComponent<AnimatorComponent>();

    static float idleDirection = 1.f;
    float direction = (float)(IsKeyDown(KEY_RIGHT) - IsKeyDown(KEY_LEFT));
    velocity.x = moveSpeed * direction;
    tc.position.x += velocity.x * GetFrameTime();

    if (direction != 0.f)
    {
        (direction < 0.f) ? idleDirection = -1.f : idleDirection = 1.f;
        ac.SetAnimationIndex(ANIM_PLAYER_WALK);
        src.source.width *= direction;
    }
    else
    {
        ac.SetAnimationIndex(ANIM_PLAYER_IDLE);
        src.source.width *= idleDirection;
    }
}
