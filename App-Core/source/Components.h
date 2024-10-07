#pragma once
#include "Animation.h"
#include <raylib.h>
#include <string>
#include <vector>

namespace Scene
{
    struct TransformComponent
    {
        bool isEnabled = false;
        Vector2 position;
        float rotation;
        Vector2 scale;

        TransformComponent()
        {
            position = {0.f, 0.f};
            rotation = 0.f;
            scale = {1.f, 1.f};
        }

        TransformComponent(Vector2 position, float rotation, Vector2 scale)
        {
            this->position = position;
            this->rotation = rotation;
            this->scale = scale;
        }
    };

    struct SpriteRendererComponent
    {
        bool isEnabled = false;
        Vector2 origin;
        Rectangle source;
        Texture2D* texture = NULL;
        Color tint = WHITE;

        SpriteRendererComponent() = default;
        SpriteRendererComponent(Texture2D* texture, Vector2 origin = {0.f, 0.f})
        {
            this->origin = origin;

            if (texture)
            {
                source = {0.f, 0.f, (float)texture->width, (float)texture->height};
                this->texture = texture;
            }
        }
    };

    struct AnimatorComponent
    {
        bool isEnabled = false;
        u32 animationIndex = 0;
        std::vector<Animation> animations;

        AnimatorComponent() = default;
        AnimatorComponent(const Animation* animations, u32 animationCount, bool playOnLoad = false)
        {
            this->animations.resize(animationCount);

            for (u32 i = 0; i < animationCount; i++)
                this->animations[i] = animations[i];

            if (playOnLoad)
                this->animations[animationIndex].Play();
        }

        inline void Play() { animations[animationIndex].Play(); }
        inline void Stop() { animations[animationIndex].Stop(); }
        inline void SetAnimationIndex(u32 animationIndex)
        {
            this->animationIndex = animationIndex;
            animations[this->animationIndex].Play();
        }
    };

    struct BoxColliderComponent
    {
        bool isEnabled = false;
        bool drawCollider = true;
        Rectangle box;
        Vector2 offset = {0.f, 0.f};
        float left = 0.f;
        float right = 0.f;
        float top = 0.f;
        float bottom = 0.f;

        BoxColliderComponent() = default;
        BoxColliderComponent(TransformComponent& transform, Vector2 size, Vector2 offset)
        {
            this->offset = offset;

            box.x = transform.position.x + offset.x;
            box.y = transform.position.y + offset.y;
            box.width = size.x * transform.scale.x;
            box.height = size.y * transform.scale.y;

            left = box.x;
            right = box.x + box.width;
            top = box.y;
            bottom = box.y + box.height;
        }
    };

    struct RigidbodyComponent
    {
        bool isEnabled = false;
        float mass = 1.f;
        float gravityScale = 1.f;
        float drag = 1.f;
        Vector2 velocity;
        Vector2 position;

        RigidbodyComponent() = default;
        RigidbodyComponent(float xVelocity, float yVelocity) { this->velocity = (v2){xVelocity, yVelocity}; }
        RigidbodyComponent(Vector2 velocity, float mass = 1.f, float gravityScale = 1.f, float drag = 1.f)
        {
            this->position = (v2){0.f, 0.f};
            this->velocity = velocity;
            this->mass = mass;
            this->gravityScale = gravityScale;
            this->drag = drag;
        }
    };

}
