#pragma once
#include "Base.h"
#include <raylib.h>

namespace Scene
{
    class Animation
    {
    public:
        Animation() = default;
        Animation(u32 frameSpeed, u32 frameCount, Vector2 sliceDimensions);

        inline bool IsPlaying() { return m_isPlaying; }
        inline Rectangle& GetSource() { return m_source; }

        inline void Play() { m_isPlaying = true; }
        inline void Stop() { m_isPlaying = false; }

        void Update();

    private:
        u32 m_frameSpeed;
        u32 m_frameCount;
        u32 m_frameCounter = 0;
        u32 m_currentFrame = 0;
        Rectangle m_source;

        bool m_isPlaying = false;
    };
}
