#pragma once
#include "../Core.h"
#include "GameEntity.h"
#include "../Event/EventManager.h"
#include "../Event/RenderableEntityCreatedEvent.h"
namespace GameEngine
{
	class ENGINE_API RenderableEntity : public GameEntity
	{
	public:
		RenderableEntity();
	};
}
