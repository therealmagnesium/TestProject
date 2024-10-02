#pragma once
#include <raylib.h>
#include <string>

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
        Vector2 origin = {0.f, 0.f};
        Rectangle source;
        Texture2D* texture = NULL;
        Color tint = WHITE;

        SpriteRendererComponent() = default;
        SpriteRendererComponent(Texture2D* texture)
        {
            if (texture)
            {
                source = {0.f, 0.f, (float)texture->width, (float)texture->height};
                this->texture = texture;
            }
        }
    };

}
