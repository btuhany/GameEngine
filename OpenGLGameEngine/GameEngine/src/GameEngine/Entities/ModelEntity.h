#pragma once
#include "RenderableEntity.h"
#include "../Components/ModelRendererComponent.h"
#include "../Debug/Log.h"
namespace GameEngine
{
	class ENGINE_API ModelEntity : public RenderableEntity
	{
	public:
		ModelEntity(std::shared_ptr<ModelRenderData> modelRenderData);
		std::shared_ptr<ModelRendererComponent> renderer;
	};
}

