#include "MeshEntity.h"
namespace GameEngine
{
	MeshEntity::MeshEntity() : RenderableEntity()
	{
		//renderer = std::make_shared<MeshRenderer>();
		//AddComponent<MeshRenderer>(renderer);
	}

	void MeshEntity::Render(glm::mat4 projectionMatrix)
	{
		m_Renderer->RenderObjectWithShader(transform->GetModelMatrix(), projectionMatrix, m_RenderData);
	}
}