#pragma once
#include "Types.h"
#include "raylib.h"
#include <vector>

class PlatformManager
{
public:
    PlatformManager(const ScreenSize& screenSize, RandomFunc randFunc);
    void applyScroll(float offset);

    const std::vector<Rectangle>& platforms() const;

private:
    const ScreenSize c_screenSize;
    const float c_verticalSpacing;
    std::vector<Rectangle> m_platforms;
    RandomFunc m_randFunc;

    void regeneratePlatform(Rectangle& platform);
};