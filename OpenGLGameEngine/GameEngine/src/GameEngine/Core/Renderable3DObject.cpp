#include "Renderable3DObject.h"


namespace GameEngine {
	Renderable3DObject::Renderable3DObject()
	{
		m_TransformModelMatrix = glm::mat4(1.0f);
	}

	Renderable3DObject::~Renderable3DObject()
	{
		printf("deleted renderable object! \n");
		//delete m_Renderer;
		//delete m_RenderableData;
	}

	Renderable3DObject::Renderable3DObject(MeshRenderer* renderer, RenderableData* renderableData)
	{
		m_Renderer = renderer;
		m_RenderableData = renderableData;
		m_TransformModelMatrix = glm::mat4(1.0f);
	}

	void Renderable3DObject::Render(glm::mat4 projectionMatrix, glm::mat4 viewMatrix, Camera* mainCamera, DirectionalLight* dirLight)
	{
		m_Renderer->RenderObjectWithShader(m_TransformModelMatrix, projectionMatrix, m_RenderableData);
	}

	void Renderable3DObject::RenderDirectionalShadowMap(DirectionalLight* dirLight)
	{
		m_Renderer->RenderObjectForDirectionalShadow(m_TransformModelMatrix, dirLight, m_RenderableData);
	}

	void Renderable3DObject::RenderOmniShadowMap(PointLight* pointLight)
	{
		m_Renderer->RenderObjectForOmniShadow(m_TransformModelMatrix, pointLight, m_RenderableData);
	}

	void Renderable3DObject::TranslateTransform(glm::vec3 translateVector)
	{
		m_TransformModelMatrix = glm::translate(m_TransformModelMatrix, translateVector);
	}

	void Renderable3DObject::RotateTransform(float angle, glm::vec3 rotateVector)
	{
		const float toRadians = 3.14159265f / 180.0f;
		m_TransformModelMatrix = glm::rotate(m_TransformModelMatrix, angle * toRadians, rotateVector);
	}

	void Renderable3DObject::ScaleTransform(glm::vec3 scaleVector)
	{
		m_TransformModelMatrix = glm::scale(m_TransformModelMatrix, scaleVector);
	}

	Shader* Renderable3DObject::GetRenderShader()
	{
		return m_Renderer->GetRenderShader();
	}

	void Renderable3DObject::ClearRenderableObject()
	{
		delete m_RenderableData;
	}
}