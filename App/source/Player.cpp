#include "Player.h"
#include "Base.h"

#include <Application.h>
#include <raylib.h>

using namespace Core;
using namespace Scene;

#define GRAVITY 35.f
#define DRAG 0.7f

Player CreatePlayer()
{
    Player player;

    player.texture = new Texture2D;
    *player.texture = LoadTexture("assets/textures/sunnyland/Packs/Sunnyland/spritesheets/player.png");
    player.animations[ANIM_PLAYER_IDLE] = Animation(10, 4, 0, 11, 6, 0, *player.texture);
    player.animations[ANIM_PLAYER_WALK] = Animation(12, 6, 0, 11, 6, 1, *player.texture);
    player.animations[ANIM_PLAYER_CROUCH] = Animation(6, 3, 0, 12, 6, 3, *player.texture);

    player.entity = App->CreateEntity("Player");
    auto& tc = player.entity->AddComponent<TransformComponent>((Vector2){100.f, 100.f}, 0.f, (Vector2){4.f, 4.f});
    player.entity->AddComponent<SpriteRendererComponent>(player.texture);
    player.entity->AddComponent<AnimatorComponent>(player.animations, ANIM_PLAYER_COUNT).Play();
    player.entity->AddComponent<BoxColliderComponent>(tc, (Vector2){20.f, 22.f}, (Vector2){20.f, 40.f});

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
    auto& bcc = entity->GetComponent<BoxColliderComponent>();

    static float idleDirection = 1.f;
    float direction = (float)(IsKeyDown(KEY_RIGHT) - IsKeyDown(KEY_LEFT));

    velocity.x += moveSpeed * direction;
    velocity.x *= DRAG;
    tc.position.x += velocity.x * GetFrameTime();

    velocity.y += GRAVITY;

    if (bcc.bottom > App->GetSpecification().windowHeight)
    {
        velocity.y = 0.f;
        isGrounded = true;
        tc.position.y = App->GetSpecification().windowHeight - bcc.box.height - bcc.offset.y;
    }

    if (IsKeyPressed(KEY_UP) && isGrounded)
    {
        velocity.y = -1000.f;
        isGrounded = false;
    }

    tc.position.y += velocity.y * GetFrameTime();

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
