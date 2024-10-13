#pragma once
#include "../Core.h"
#include "../Components/Component.h"
#include "Event.h" 
namespace GameEngine
{
	enum class ComponentAction
	{
		None = 0,
		Added = 1,
		Removed = 2,
		OwnerPreDestroyed = 3
	};

	class ENGINE_API ComponentEvent : public EventBase<ComponentEvent>
	{
	public:
		ComponentAction compAction;
		std::shared_ptr<Component> comp;
	};
}
