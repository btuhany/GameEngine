#include "Vector3.h"
namespace GameEngine 
{
    Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

    Vector3 Vector3::operator+(const Vector3& other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }
    
    Vector3 Vector3::operator-(const Vector3& other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    Vector3 Vector3::operator*(float scalar) const {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }

    Vector3 Vector3::operator/(float scalar) const {
        return Vector3(x / scalar, y / scalar, z / scalar);
    }

    float Vector3::dot(const Vector3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    Vector3 Vector3::cross(const Vector3& other) const {
        return Vector3(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }

    float Vector3::magnitude() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    Vector3 Vector3::normalize() const {
        float mag = magnitude();
        return Vector3(x / mag, y / mag, z / mag);
    }

    //Vector3 Vector3::UnclampedLerp(const Vector3& a, const Vector3& b, float t, std::function<float(float)> ease) {
    //    if (ease) {
    //        t = ease(t);
    //    }
    //    return a + (b - a) * t;
    //}

    Vector3 Vector3::UnclampedLerp(const Vector3& a, const Vector3& b, float t)
    {
        return a + (b - a) * t;
    }

    const Vector3 Vector3::up(0.0f, 1.0f, 0.0f);
    const Vector3 Vector3::down(0.0f, -1.0f, 0.0f);
    const Vector3 Vector3::left(-1.0f, 0.0f, 0.0f);
    const Vector3 Vector3::right(1.0f, 0.0f, 0.0f);
    const Vector3 Vector3::zero(0.0f, 0.0f, 0.0f);
    const Vector3 Vector3::forward(0.0f, 0.0f, 1.0f);
    const Vector3 Vector3::back(0.0f, 0.0f, -1.0f);

}