#pragma once
#include "RenderableEntity.h"
#include "../Components/MeshRendererComponent.h"
#include "../Debug/Log.h"
namespace GameEngine
{
	class ENGINE_API MeshEntity : public RenderableEntity
	{
	public:
		MeshEntity();
		//void Render(glm::mat4 projectionMatrix) override;
		//TODOby initialzie
		std::shared_ptr<MeshRendererComponent> renderer;
		void HandleOnRegisteredToScene() override;
	};
}
