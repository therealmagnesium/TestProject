#pragma once
#include "Base.h"
#include <raylib.h>

namespace Scene
{
    enum AnimationFrameMode
    {
        ANIM_FRAME_HORIZONTAL = 0,
        ANIM_FRAME_VERTICAL,
        ANIM_FRAME_COUNT,
    };

    class Animation
    {
    public:
        Animation() = default;
        Animation(u32 frameSpeed, u32 frameCountX, u32 frameCountY, u32 rowCount, u32 colCount, u32 frameOffset,
                  const Texture& texture);

        inline bool IsPlaying() { return m_isPlaying; }
        inline Rectangle& GetSource() { return m_source; }

        inline void Play() { m_isPlaying = true; }
        inline void Stop() { m_isPlaying = false; }
        inline void SetFrameMode(AnimationFrameMode mode) { m_animFrameMode = mode; }

        void Update();

    private:
        u32 m_frameSpeed;

        u32 m_frameCountX;
        u32 m_frameCountY;
        Vector2 m_frameSize;

        u32 m_frameOffset = 0;
        u32 m_frameCounter = 0;
        u32 m_currentFrame = 0;

        u32 m_rowCount;
        u32 m_colCount;

        Rectangle m_source;
        AnimationFrameMode m_animFrameMode = ANIM_FRAME_HORIZONTAL;

        bool m_isPlaying = false;
    };
}
