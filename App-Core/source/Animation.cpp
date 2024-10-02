#include "Animation.h"
#include "Base.h"

#include <raylib.h>

namespace Scene
{
    Animation::Animation(u32 frameSpeed, u32 frameCount, Vector2 sliceDimensions)
    {
        m_frameSpeed = frameSpeed;
        m_frameCount = frameCount;
        m_source = {0.f, 0.f, sliceDimensions.x, sliceDimensions.y};
    }

    void Animation::Update()
    {
        if (m_isPlaying)
        {
            m_frameCounter++;

            if (m_frameCounter >= (60.f / m_frameSpeed))
            {
                m_frameCounter = 0;
                m_currentFrame++;

                if (m_currentFrame > m_frameCount - 1)
                    m_currentFrame = 0;

                m_source.x = (float)m_currentFrame * m_source.width;
            }
        }
    }
}
