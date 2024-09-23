#pragma once
#include "RenderableEntity.h"
#include "../Components/ModelRendererComponent.h"
#include "../Debug/Log.h"
namespace GameEngine
{
	class ENGINE_API ModelEntity : public RenderableEntity
	{
	public:
		ModelEntity();
		//void Render(glm::mat4 projectionMatrix) override;
		//TODOby initialize
		std::shared_ptr<ModelRendererComponent> renderer;
		void HandleOnRegisteredToScene() override;
	};
}

