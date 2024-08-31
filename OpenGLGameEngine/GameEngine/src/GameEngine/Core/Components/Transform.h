#pragma once
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc\matrix_transform.hpp>
#include "../Core.h"
#include "../Component.h"

namespace GameEngine
{
	class ENGINE_API Transform : public Component
	{
	public:
		void Translate(glm::vec3 translateVector);
		void Rotate(float angle, glm::vec3 rotateVector);
		void Scale(glm::vec3 scaleVector);
		glm::mat4 GetModelMatrix();
	private:
		glm::mat4 m_ModelMatrix = glm::mat4(1.0f);
	};
}

