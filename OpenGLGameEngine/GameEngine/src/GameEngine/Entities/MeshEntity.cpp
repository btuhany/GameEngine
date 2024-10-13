#include "MeshEntity.h"
namespace GameEngine
{
	MeshEntity::MeshEntity(std::shared_ptr<MeshRenderData> meshRenderData) : RenderableEntity()
	{
		renderer = std::make_shared<MeshRendererComponent>();
		renderer->setMeshRenderData(meshRenderData);
		AddComponent<MeshRendererComponent>(renderer);
	}
}