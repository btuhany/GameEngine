#pragma once
#include <cmath>
#include "../Core.h"
namespace GameEngine
{
    struct ENGINE_API Vector2 {
        float x;
        float y;

        Vector2();
        Vector2(float x, float y);

        Vector2 operator+(const Vector2& other) const;
        Vector2 operator-(const Vector2& other) const;
        Vector2 operator*(float scalar) const;

        float length() const;
        Vector2 normalize() const;
    };
}

