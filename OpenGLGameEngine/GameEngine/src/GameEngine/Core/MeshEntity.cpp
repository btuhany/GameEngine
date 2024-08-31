#include "MeshEntity.h"
namespace GameEngine
{
	MeshEntity::MeshEntity() : RenderableEntity()
	{
		renderer = std::make_shared<MeshRendererComponent>();
		AddComponent<MeshRendererComponent>(renderer);
	}

	void MeshEntity::Render(glm::mat4 projectionMatrix)
	{
		LOG_CORE_INFO("a");
		renderer->Render(projectionMatrix);
	}
}