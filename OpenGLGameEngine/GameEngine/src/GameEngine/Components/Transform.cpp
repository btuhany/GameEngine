#include "Transform.h"


namespace GameEngine
{
	void Transform::Translate(glm::vec3 translateVector)
	{
		m_Position += translateVector;
		updateModelMatrix();
	}

	void Transform::Rotate(float angle, glm::vec3 rotateVector)
	{
		const float toRadians = 3.14159265f / 180.0f;
		m_Rotation = glm::rotate(glm::mat4(1.0f), angle * toRadians, rotateVector) * m_Rotation;
		updateModelMatrix();
	}

	void Transform::Scale(glm::vec3 scaleVector)
	{
		m_Scale = scaleVector;
		updateModelMatrix();
	}
	void Transform::SetPosition(glm::vec3 newPosition)
	{
		m_Position = newPosition;
		updateModelMatrix();
	}
	glm::mat4 Transform::GetModelMatrix()
	{
		return m_ModelMatrix;
	}
	glm::vec3 Transform::GetPosition()
	{
		return m_Position;
	}
	ComponentType Transform::getType()
	{
		return ComponentType::Transform;
	}
	void Transform::updateModelMatrix()
	{
		m_ModelMatrix = glm::translate(glm::mat4(1.0f), m_Position) * glm::mat4(m_Rotation) * glm::scale(glm::mat4(1.0f), m_Scale);
	}
}