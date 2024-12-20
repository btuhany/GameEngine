#pragma once
#include "Vector3.h"
#include "glm/vec3.hpp"
namespace GameEngine
{
	class VectorUtility
	{
    public:
        static glm::vec3 Vector3ToGlmVec3(const Vector3& a)
        {
            return glm::vec3(a.x, a.y, a.z);
        }
        static Vector3 GlmVec3ToVector3(glm::vec3 a)
        {
            return Vector3(a.x, a.y, a.z);
        }
	};
}