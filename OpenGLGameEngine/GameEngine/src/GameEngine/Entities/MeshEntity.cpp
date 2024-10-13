#include "MeshEntity.h"
namespace GameEngine
{
	MeshEntity::MeshEntity() : RenderableEntity()
	{
		renderer = std::make_shared<MeshRendererComponent>();
		AddComponent<MeshRendererComponent>(renderer);
	}
}