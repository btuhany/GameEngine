#include "Object.h"



Object::Object()
{
	m_TransformModelMatrix = glm::mat4(1.0f);
}

Object::~Object()
{
	m_Renderer = nullptr;
	m_Shader = nullptr;
}

Object::Object(Renderer* renderer)
{
	m_Renderer = renderer;
	m_TransformModelMatrix = glm::mat4(1.0f);
}

void Object::Start()
{
}

void Object::Tick()
{
}

void Object::RenderUpdate(glm::mat4 projectionMatrix, glm::mat4 viewMatrix, Camera* mainCamera)
{
	m_Renderer->RenderUpdate(m_TransformModelMatrix, projectionMatrix, viewMatrix, mainCamera);
}

void Object::TranslateTransform(glm::vec3 translateVector)
{
	m_TransformModelMatrix = glm::translate(m_TransformModelMatrix, translateVector);
}

void Object::RotateTransform(float angle, glm::vec3 rotateVector)
{
	const float toRadians = 3.14159265f / 180.0f;
	m_TransformModelMatrix = glm::rotate(m_TransformModelMatrix, angle * toRadians, rotateVector);
}

void Object::ScaleTransform(glm::vec3 scaleVector)
{
	m_TransformModelMatrix = glm::scale(m_TransformModelMatrix, scaleVector);
}
