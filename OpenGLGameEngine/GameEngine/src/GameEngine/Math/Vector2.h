#pragma once
#include <cmath>
#include "../Core.h"
#include "glm/glm.hpp"
#include "Vector3.h"
namespace GameEngine
{
    struct ENGINE_API Vector2 {
        float x;
        float y;

        Vector2();
        Vector2(float x, float y);
        Vector2(glm::vec3 glmVec3);
        Vector2(Vector3 vec3);

        Vector2 operator+(const Vector2& other) const;
        Vector2 operator-(const Vector2& other) const;
        Vector2 operator*(float scalar) const;
        bool operator==(const Vector2& other) const;

        float length() const;
        Vector2 normalize() const;


        static const Vector2 up;
        static const Vector2 down;
        static const Vector2 left;
        static const Vector2 right;
        static const Vector2 zero;
    };
}

