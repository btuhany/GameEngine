#pragma once
#include "../Core.h"
#include "../Components/RendererComponent.h"
#include "Event.h"

namespace GameEngine
{
	enum class RendererComponentType
	{
		None = 0,
		MeshRenderer = 1,
		ModelRenderer = 2
	};

	class ENGINE_API RenderableEntityCreatedEvent : public EventBase<RenderableEntityCreatedEvent>
	{
	public:
		RendererComponentType ComponentType;
		std::shared_ptr<RendererComponent> Component;
	};

}

