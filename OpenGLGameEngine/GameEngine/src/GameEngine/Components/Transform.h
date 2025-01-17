#pragma once
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc\matrix_transform.hpp>
#include "../Core.h"
#include "../Components/Component.h"
#include "../Math/Vector3.h"
namespace GameEngine
{
	class ENGINE_API Transform : public Component
	{
	public:
		void Translate(glm::vec3 translateVector);
		void Rotate(float angle, glm::vec3 rotateVector);
		void SetScale(glm::vec3 scaleVector);
		void Scale(float xVal, float yVal, float zVal);
		void SetPosition(glm::vec3 newPosition);
		void SetPosition(Vector3 newPos);
		void ResetRotation();
		glm::mat4 GetModelMatrix();
		glm::vec3 getPosition();
		glm::mat4 getRotation();
		glm::vec3 getScale();
		ComponentType getType() override;
	private:
		glm::mat4 m_ModelMatrix = glm::mat4(1.0f);
		glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 m_Scale = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::mat4 m_Rotation = glm::mat4(1.0f);
		void updateModelMatrix();
	};
}

