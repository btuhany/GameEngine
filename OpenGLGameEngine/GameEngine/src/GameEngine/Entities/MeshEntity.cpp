#include "MeshEntity.h"
namespace GameEngine
{
	MeshEntity::MeshEntity() : RenderableEntity()
	{
		renderer = std::make_shared<MeshRendererComponent>();
		AddComponent<MeshRendererComponent>(renderer);
	}

	//void MeshEntity::HandleOnRegisteredToScene()
	//{
	//	auto event = std::make_shared<RenderableEntityCreatedEvent>();
	//	event->Component = GetComponent<MeshRendererComponent>();
	//	EventManager::GetInstance().Publish(event);
	//}
}