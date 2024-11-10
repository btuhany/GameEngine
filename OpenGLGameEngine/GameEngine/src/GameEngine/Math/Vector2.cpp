#include "Vector2.h"

namespace GameEngine
{
    Vector2::Vector2() : x(0), y(0) {}
    Vector2::Vector2(float x, float y) : x(x), y(y) {}

    Vector2::Vector2(glm::vec3 glmVec3)
    {
        x = glmVec3.x;
        y = glmVec3.y;
    }

    Vector2::Vector2(Vector3 vec3)
    {
        x = vec3.x;
        y = vec3.y;
    }

    Vector2 Vector2::operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2 Vector2::operator-(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }

    Vector2 Vector2::operator*(float scalar) const {
        return Vector2(x * scalar, y * scalar);
    }

    Vector2 Vector2::operator/(float scalar) const
    {
        return Vector2(x / scalar, y / scalar);
    }

    bool Vector2::operator==(const Vector2& other) const {
        return x == other.x && y == other.y;
    }

    float Vector2::length() const {
        return std::sqrt(x * x + y * y);
    }

    Vector2 Vector2::normalize() const {
        float len = length();
        return (len > 0) ? Vector2(x / len, y / len) : Vector2();
    }

    float Vector2::Dot(Vector2 other)
    {
        return x * other.x + y * other.y;
    }

    const bool Vector2::IsAligned(Vector2 aVec, Vector2 bVec, float threshold)
    {
        Vector2 normA = aVec.normalize();
        Vector2 normB = bVec.normalize();

        float dotProduct = normA.Dot(normB);

        return dotProduct >= threshold;
    }

    std::string Vector2::toString() const
    {
        std::ostringstream oss;
        oss << "(" << x << ", " << y << ")";
        return oss.str();
    }

    const Vector2 Vector2::up(0.0f, 1.0f);
    const Vector2 Vector2::down(0.0f, -1.0f);
    const Vector2 Vector2::left(-1.0f, 0.0f);
    const Vector2 Vector2::right(1.0f, 0.0f);
    const Vector2 Vector2::zero(0.0f, 0.0f);
}
