#pragma once

#include <functional>

struct ScreenSize
{
    int width;
    int height;
};

using RandomFunc = std::function<float(float, float)>;