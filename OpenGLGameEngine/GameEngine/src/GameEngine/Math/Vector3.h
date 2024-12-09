#pragma once
#include <cmath>
#include "../Core.h"
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




        static const Vector3 up;
        static const Vector3 down;
        static const Vector3 left;
        static const Vector3 right;
        static const Vector3 zero;
        static const Vector3 forward;
        static const Vector3 back;
	};
}

