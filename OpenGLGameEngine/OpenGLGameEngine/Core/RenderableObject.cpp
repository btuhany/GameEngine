#include "RenderableObject.h"



RenderableObject::RenderableObject()
{
	m_TransformModelMatrix = glm::mat4(1.0f);
}

RenderableObject::~RenderableObject()
{
	m_Renderer = nullptr;
	m_Shader = nullptr;
}

RenderableObject::RenderableObject(Renderer* renderer, RenderableData* renderableData)
{
	m_Renderer = renderer;
	m_RenderableData = renderableData;
	m_TransformModelMatrix = glm::mat4(1.0f);
}

void RenderableObject::Render(glm::mat4 projectionMatrix, glm::mat4 viewMatrix, Camera* mainCamera)
{
	m_Renderer->Draw(m_TransformModelMatrix, projectionMatrix, viewMatrix, mainCamera, m_RenderableData);
}

void RenderableObject::TranslateTransform(glm::vec3 translateVector)
{
	m_TransformModelMatrix = glm::translate(m_TransformModelMatrix, translateVector);
}

void RenderableObject::RotateTransform(float angle, glm::vec3 rotateVector)
{
	const float toRadians = 3.14159265f / 180.0f;
	m_TransformModelMatrix = glm::rotate(m_TransformModelMatrix, angle * toRadians, rotateVector);
}

void RenderableObject::ScaleTransform(glm::vec3 scaleVector)
{
	m_TransformModelMatrix = glm::scale(m_TransformModelMatrix, scaleVector);
}
