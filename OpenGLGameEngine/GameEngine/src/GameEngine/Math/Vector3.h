#pragma once
#include <cmath>
#include "../Core.h"
#include <functional>
namespace GameEngine
{
	struct ENGINE_API Vector3
	{
        float x, y, z;

        Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f);

        Vector3 operator+(const Vector3& other) const;

        Vector3 operator-(const Vector3& other) const;

        Vector3 operator*(float scalar) const;

        Vector3 operator/(float scalar) const;

        float dot(const Vector3& other) const;

        Vector3 cross(const Vector3& other) const;

        float magnitude() const;

        Vector3 normalize() const;

        //static Vector3 UnclampedLerp(const Vector3& a, const Vector3& b, float t, std::function<float(float)> ease = nullptr);

        static Vector3 UnclampedLerp(const Vector3& a, const Vector3& b, float t);

        static const Vector3 up;
        static const Vector3 down;
        static const Vector3 left;
        static const Vector3 right;
        static const Vector3 zero;
        static const Vector3 forward;
        static const Vector3 back;
	};
}

