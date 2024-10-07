#include "EntityManager.h"
#include "Components.h"
#include "raylib.h"

#include <algorithm>
#include <memory>
#include <string>

namespace Scene
{
    std::shared_ptr<Entity> EntityManager::AddEntity(const char* tag)
    {
        std::shared_ptr<Entity> entity = std::make_shared<Entity>(m_totalEntities++, tag);
        entity->SetActive(true);
        m_toAdd.push_back(entity);
        return entity;
    }

    void EntityManager::Update()
    {
        for (auto& entity : m_toAdd)
        {
            const char* entityTag = entity->GetTag();
            m_entities.push_back(entity);
            m_entityMap[entityTag].push_back(entity);
        }

        for (u64 i = 0; i < m_entities.size(); i++)
        {
            auto& entity = m_entities[i];
            const char* entityTag = entity->GetTag();
            if (!entity->IsAlive())
            {
                m_entities.erase(m_entities.begin() + i);
                m_entityMap[entityTag].erase(m_entities.begin() + i);
            }
        }

        m_toAdd.clear();

        for (u64 i = 0; i < m_entities.size(); i++)
        {
            std::shared_ptr<Entity> entity = m_entities[i];
            if (entity->HasComponent<SpriteRendererComponent>() && entity->HasComponent<AnimatorComponent>())
            {
                SpriteRendererComponent& src = entity->GetComponent<SpriteRendererComponent>();
                AnimatorComponent& ac = entity->GetComponent<AnimatorComponent>();

                if (entity->IsActive() && src.isEnabled && ac.isEnabled)
                {
                    ac.animations[ac.animationIndex].Update();
                    src.source = ac.animations[ac.animationIndex].GetSource();
                }
            }

            if (entity->HasComponent<BoxColliderComponent>() && entity->HasComponent<TransformComponent>())
            {
                TransformComponent& tc = entity->GetComponent<TransformComponent>();
                BoxColliderComponent& bcc = entity->GetComponent<BoxColliderComponent>();

                bcc.box.x = tc.position.x + bcc.offset.x;
                bcc.box.y = tc.position.y + bcc.offset.y;

                bcc.left = bcc.box.x;
                bcc.right = bcc.box.x + bcc.box.width;
                bcc.top = bcc.box.y;
                bcc.bottom = bcc.box.y + bcc.box.height;
            }
        }
    }

    void EntityManager::DrawEntities()
    {
        for (u64 i = 0; i < m_entities.size(); i++)
        {
            std::shared_ptr<Entity> entity = m_entities[i];
            if (entity->HasComponent<TransformComponent>() && entity->HasComponent<SpriteRendererComponent>())
            {
                TransformComponent& tc = entity->GetComponent<TransformComponent>();
                SpriteRendererComponent& src = entity->GetComponent<SpriteRendererComponent>();

                if (entity->IsActive() && src.isEnabled)
                {
                    if (src.texture && src.texture->id != 0)
                    {
                        Rectangle dest = {tc.position.x, tc.position.y, abs(src.source.width) * tc.scale.x,
                                          abs(src.source.height) * tc.scale.y};
                        DrawTexturePro(*src.texture, src.source, dest, src.origin, tc.rotation, src.tint);
                    }
                    else
                    {
                        Rectangle rect = {tc.position.x, tc.position.y, 64.f * tc.scale.x, 64.f * tc.scale.y};
                        DrawRectanglePro(rect, src.origin, tc.rotation, src.tint);
                    }
                }
            }

            if (entity->HasComponent<BoxColliderComponent>())
            {
                BoxColliderComponent& bcc = entity->GetComponent<BoxColliderComponent>();
                DrawRectangleLinesEx(bcc.box, 6.f, GREEN);
            }
        }
    }

    EntityVec& EntityManager::GetEntities() { return m_entities; }
    EntityVec& EntityManager::GetEntities(const char* tag) { return m_entityMap[tag]; }
}
