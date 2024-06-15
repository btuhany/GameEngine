#include "RenderableObject.h"



RenderableObject::RenderableObject()
{
	m_TransformModelMatrix = glm::mat4(1.0f);
}

RenderableObject::~RenderableObject()
{
	printf("deleted renderable object! \n");
	//delete m_Renderer;
	//delete m_RenderableData;
	//delete m_Shader;
}

RenderableObject::RenderableObject(Renderer* renderer, RenderableData* renderableData)
{
	m_Renderer = renderer;
	m_RenderableData = renderableData;
	m_TransformModelMatrix = glm::mat4(1.0f);
}

void RenderableObject::Render(glm::mat4 projectionMatrix, glm::mat4 viewMatrix, Camera* mainCamera, DirectionalLight* dirLight)
{
	m_Renderer->RenderObjectWithShader(m_TransformModelMatrix, projectionMatrix, viewMatrix, mainCamera, m_RenderableData, dirLight);
}

void RenderableObject::RenderShadowMap(DirectionalLight* dirLight)
{
	m_Renderer->RenderObjectForDirectionalShadow(m_TransformModelMatrix, dirLight, m_RenderableData);
}

void RenderableObject::RenderOmniShadowMap(PointLight* pointLight)
{
	m_Renderer->RenderObjectForOmniShadow(m_TransformModelMatrix, pointLight, m_RenderableData);
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
