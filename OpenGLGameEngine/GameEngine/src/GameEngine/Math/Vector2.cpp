#include "Vector2.h"

namespace GameEngine
{
    Vector2::Vector2() : x(0), y(0) {}
    Vector2::Vector2(float x, float y) : x(x), y(y) {}

    Vector2 Vector2::operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2 Vector2::operator-(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }

    Vector2 Vector2::operator*(float scalar) const {
        return Vector2(x * scalar, y * scalar);
    }

    float Vector2::length() const {
        return std::sqrt(x * x + y * y);
    }

    Vector2 Vector2::normalize() const {
        float len = length();
        return (len > 0) ? Vector2(x / len, y / len) : Vector2();
    }
}
