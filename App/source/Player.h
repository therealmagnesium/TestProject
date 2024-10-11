#pragma once
#include <Animation.h>
#include <Base.h>
#include <Entity.h>
#include <Tilemap.h>

#include <raylib.h>
#include <memory>

using namespace Scene;

enum PlayerAnimation
{
    ANIM_PLAYER_IDLE = 0,
    ANIM_PLAYER_WALK,
    ANIM_PLAYER_CROUCH,
    ANIM_PLAYER_COUNT
};

struct Player
{
    std::shared_ptr<Entity> entity;

    float direction = 0.f;
    float moveSpeed = 400.f;
    float jumpForce = 10.f;
    bool isGrounded = false;

    Texture2D* texture;
    Animation animations[ANIM_PLAYER_COUNT];

    inline TransformComponent& GetTransform() { return entity->GetComponent<TransformComponent>(); }
    inline SpriteRendererComponent& GetSprite() { return entity->GetComponent<SpriteRendererComponent>(); }
    inline AnimatorComponent& GetAnimator() { return entity->GetComponent<AnimatorComponent>(); }
    inline BoxColliderComponent& GetCollider() { return entity->GetComponent<BoxColliderComponent>(); }

    void HandleMovement();
    void Animate();
    void HandleCollisions(Tilemap& tilemap);
    void Update(Tilemap& tilemap);
};

Player CreatePlayer();
void FreePlayer(Player& player);
