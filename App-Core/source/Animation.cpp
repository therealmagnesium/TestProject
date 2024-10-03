#include "Animation.h"
#include "Base.h"

#include <raylib.h>

namespace Scene
{
    Animation::Animation(u32 frameSpeed, u32 frameCountX, u32 frameCountY, u32 rowCount, u32 colCount, u32 frameOffset,
                         const Texture& texture)
    {
        m_frameSpeed = frameSpeed;
        m_frameCountX = frameCountX;
        m_frameCountY = frameCountY;
        m_rowCount = rowCount;
        m_colCount = colCount;
        m_frameOffset = frameOffset;
        m_frameSize = {(float)texture.width / colCount, (float)texture.height / rowCount};
        m_source = {0.f, 0.f, m_frameSize.x, m_frameSize.y};
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

                switch (m_animFrameMode)
                {
                    case ANIM_FRAME_HORIZONTAL:
                    {
                        if (m_currentFrame > m_frameCountX - 1)
                            m_currentFrame = 0;

                        m_source.x = (float)m_currentFrame * m_source.width;
                        m_source.y = (float)m_frameOffset * m_frameSize.y;
                        break;
                    }

                    case ANIM_FRAME_VERTICAL:
                    {
                        if (m_currentFrame > m_frameCountY - 1)
                            m_currentFrame = 0;

                        m_source.x = (float)m_frameOffset * m_frameSize.x;
                        m_source.y = (float)m_currentFrame * m_source.height;
                        break;
                    }

                    default:
                        break;
                }
            }
        }
    }
}
