#include "Player.h"
#include "Base.h"

#include <Application.h>
#include <raylib.h>

using namespace Core;
using namespace Scene;

Player CreatePlayer()
{
    Player player;

    player.texture = new Texture2D;
    *player.texture = LoadTexture("assets/textures/sunnyland/Packs/Sunnyland/spritesheets/player.png");
    player.animations[ANIM_PLAYER_IDLE] = Animation(10, 4, 0, 11, 6, 0, *player.texture);
    player.animations[ANIM_PLAYER_WALK] = Animation(12, 6, 0, 11, 6, 1, *player.texture);
    player.animations[ANIM_PLAYER_CROUCH] = Animation(6, 3, 0, 12, 6, 3, *player.texture);

    player.entity = App->CreateEntity("Player");

    TransformComponent& transform = player.entity->AddComponent<TransformComponent>((v2){100.f, 100.f}, 0.f, (v2){4.f, 4.f});

    SpriteRendererComponent& spriteRenderer = player.entity->AddComponent<SpriteRendererComponent>(player.texture);
    spriteRenderer.origin = (v2){32.f, 40.f};

    AnimatorComponent& animator = player.entity->AddComponent<AnimatorComponent>(player.animations, ANIM_PLAYER_COUNT);
    animator.Play();

    BoxColliderComponent& boxCollider = player.entity->AddComponent<BoxColliderComponent>(transform, (v2){15.f, 22.f}, (v2){5.f, 0.f});
    boxCollider.drawCollider = false;

    RigidbodyComponent& rigidbody = player.entity->AddComponent<RigidbodyComponent>(0.f, 0.f);
    rigidbody.mass = 2.f;
    rigidbody.drag = 0.7f;
    rigidbody.gravityScale = 8.f;

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
    const ApplicationSpecification& appInfo = App->GetSpecification();

    auto& tc = entity->GetComponent<TransformComponent>();
    auto& src = entity->GetComponent<SpriteRendererComponent>();
    auto& ac = entity->GetComponent<AnimatorComponent>();
    auto& bcc = entity->GetComponent<BoxColliderComponent>();
    auto& rb = entity->GetComponent<RigidbodyComponent>();

    static float idleDirection = 1.f;
    float direction = (float)(IsKeyDown(KEY_RIGHT) - IsKeyDown(KEY_LEFT));

    rb.velocity.x += moveSpeed * direction;
    rb.velocity.x *= rb.drag;
    tc.position.x += rb.velocity.x * GetFrameTime();

    rb.velocity.y += GRAVITY * rb.gravityScale;

    if (bcc.bottom > appInfo.windowHeight)
    {
        rb.velocity.y = 0.f;
        isGrounded = true;
        tc.position.y = appInfo.windowHeight - bcc.box.height - bcc.offset.y;
    }

    if (IsKeyPressed(KEY_UP) && isGrounded)
    {
        rb.velocity.y = -jumpForce * rb.mass * GRAVITY * rb.gravityScale;
        isGrounded = false;
    }

    if (IsKeyPressed(KEY_B))
        bcc.drawCollider = !bcc.drawCollider;

    if (!isGrounded)
        tc.position.y += rb.velocity.y * GetFrameTime();

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
