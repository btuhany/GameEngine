#pragma once
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc\matrix_transform.hpp>
#include "../Core.h"
#include "../Components/Component.h"

namespace GameEngine
{
	class ENGINE_API Transform : public Component
	{
	public:
		void Translate(glm::vec3 translateVector);
		void Rotate(float angle, glm::vec3 rotateVector);
		void Scale(glm::vec3 scaleVector);
		glm::mat4 GetModelMatrix();
		glm::vec3 GetPosition();
	private:
		glm::mat4 m_ModelMatrix = glm::mat4(1.0f);
		glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
	};
}

