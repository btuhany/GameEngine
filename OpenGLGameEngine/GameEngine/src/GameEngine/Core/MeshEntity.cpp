#include "MeshEntity.h"
namespace GameEngine
{
	void MeshEntity::Render(glm::mat4 projectionMatrix)
	{

		m_Renderer->RenderObjectWithShader(TransformComponent.GetModelMatrix(), projectionMatrix, m_RenderData);
	}
	Shader* MeshEntity::getRenderer()
	{
		return m_Renderer->GetRenderShader();
	}
}