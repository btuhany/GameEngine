#pragma once
#include "../Core.h"
#include "../Components/RendererComponent.h"
#include "Event.h"

namespace GameEngine
{
	class ENGINE_API RenderableEntityCreatedEvent : public EventBase<RenderableEntityCreatedEvent>
	{
	public:
		std::shared_ptr<RendererComponent> Component;
	};

}

