#include "Entity.h"

namespace Scene
{
    Entity::Entity(u64 id, const char* tag)
    {
        m_id = id;
        m_tag = tag;
    }
}
