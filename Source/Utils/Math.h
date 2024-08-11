#pragma once
#include <vector>

#ifdef _WIN32
    #ifdef _EXPORTING
        #define MATH_API __declspec(dllexport)
    #elif _IMPORTING
        #define MATH_API __declspec(dllimport)
    #else
        #define MATH_API
    #endif
#else
    #define MATH_API __attribute__((visibility("default")))
#endif

namespace LifeExe
{
MATH_API int max(int x, int y);
MATH_API int factorial(int n);
MATH_API int sum(int n);
MATH_API int randomInt(int min, int max);
}  // namespace LifeExe
