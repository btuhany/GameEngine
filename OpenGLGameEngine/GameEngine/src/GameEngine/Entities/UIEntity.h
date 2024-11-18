#pragma once
#include "RenderableEntity.h"
#include "../Components/UIRendererComponent.h"
#include "../Debugging/Log.h"
#include "../Components/Component.h"
namespace GameEngine
{
	class ENGINE_API UIEntity : public RenderableEntity
	{
	public:
		UIEntity(std::shared_ptr<UIRenderData> uiRenderData);
		std::shared_ptr<UIRendererComponent> renderer;
	};
}

