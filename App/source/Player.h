#pragma once
#include <Animation.h>
#include <Base.h>
#include <Entity.h>
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
    float moveSpeed = 400.f;
    float jumpForce = 10.f;
    bool isGrounded = false;
    Texture2D* texture;
    Animation animations[ANIM_PLAYER_COUNT];

    void Update();
};

Player CreatePlayer();
void FreePlayer(Player& player);
