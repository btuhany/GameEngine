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

	/// <summary>
	/// Use scale function with float parameters instead. TODO
	/// </summary>
	/// <param name="scaleVector"></param>
	void Transform::SetScale(glm::vec3 scaleVector)
	{
		m_Scale = scaleVector;
		updateModelMatrix();
	}
	void Transform::Scale(float xVal, float yVal, float zVal)
	{
		m_Scale = glm::vec3(m_Scale.x * xVal, m_Scale.y * yVal, m_Scale.z * zVal);
		updateModelMatrix();
	}
	void Transform::SetPosition(glm::vec3 newPosition)
	{
		m_Position = newPosition;
		updateModelMatrix();
	}
	void Transform::SetPosition(Vector3 newPos)
	{
		SetPosition(glm::vec3(newPos.x, newPos.y, newPos.z));
	}
	void Transform::ResetRotation()
	{
		m_Rotation = glm::mat4(1.0f);
	}
	glm::mat4 Transform::GetModelMatrix()
	{
		return m_ModelMatrix;
	}
	glm::vec3 Transform::getPosition()
	{
		return m_Position;
	}
	glm::mat4 Transform::getRotation()
	{
		return m_Rotation;
	}
	glm::vec3 Transform::getScale()
	{
		return m_Scale;
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