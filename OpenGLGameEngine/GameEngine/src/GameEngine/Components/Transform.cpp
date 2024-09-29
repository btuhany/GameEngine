#include "Transform.h"


namespace GameEngine
{
	void Transform::Translate(glm::vec3 translateVector)
	{
		m_ModelMatrix = glm::translate(m_ModelMatrix, translateVector);
		m_Position += translateVector;
	}

	void Transform::Rotate(float angle, glm::vec3 rotateVector)
	{
		const float toRadians = 3.14159265f / 180.0f;
		m_ModelMatrix = glm::rotate(m_ModelMatrix, angle * toRadians, rotateVector);
	}

	void Transform::Scale(glm::vec3 scaleVector)
	{
		m_ModelMatrix = glm::scale(m_ModelMatrix, scaleVector);
	}
	glm::mat4 Transform::GetModelMatrix()
	{
		return m_ModelMatrix;
	}
	glm::vec3 Transform::GetPosition()
	{
		return m_Position;
	}
	ComponentType Transform::GetType()
	{
		return ComponentType::Transform;
	}
}