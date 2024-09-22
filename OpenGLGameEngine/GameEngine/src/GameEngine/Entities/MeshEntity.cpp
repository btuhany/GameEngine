#include "MeshEntity.h"
namespace GameEngine
{
	MeshEntity::MeshEntity() : RenderableEntity()
	{
		renderer = std::make_shared<MeshRendererComponent>();
		AddComponent<MeshRendererComponent>(renderer);
		
		auto event = std::make_shared<RenderableEntityCreatedEvent>();
		event->Component = std::shared_ptr<MeshRendererComponent>(renderer);
		event->ComponentType = RendererComponentType::MeshRenderer;
		EventManager::GetInstance().Publish(event);
	}

	void MeshEntity::Render(glm::mat4 projectionMatrix)
	{
		renderer->Render(projectionMatrix);
	}
}