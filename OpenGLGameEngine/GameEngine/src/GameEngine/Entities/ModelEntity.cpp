#include "ModelEntity.h"

namespace GameEngine
{
	ModelEntity::ModelEntity()
	{
		renderer = std::make_shared<ModelRendererComponent>();
		AddComponent<ModelRendererComponent>(renderer);

		auto event = std::make_shared<RenderableEntityCreatedEvent>();
		event->Component = std::shared_ptr<ModelRendererComponent>(renderer);
		event->ComponentType = RendererComponentType::ModelRenderer;
		EventManager::GetInstance().Publish(event);
	}

	//void ModelEntity::Render(glm::mat4 projectionMatrix)
	//{
	//	renderer->Render(projectionMatrix);
	//}
}
