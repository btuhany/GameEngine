#include "ModelEntity.h"

namespace GameEngine
{
	ModelEntity::ModelEntity()
	{
		renderer = std::make_shared<ModelRendererComponent>();
		AddComponent<ModelRendererComponent>(renderer);
	}

	/*void ModelEntity::HandleOnRegisteredToScene()
	{
		auto event = std::make_shared<RenderableEntityCreatedEvent>();
		event->Component = GetComponent<ModelRendererComponent>();
		EventManager::GetInstance().Publish(event);
	}*/
}
