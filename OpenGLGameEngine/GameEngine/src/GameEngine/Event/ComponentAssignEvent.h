#pragma once
#include "../Core.h"
#include "../Components/Component.h"
#include "Event.h"

namespace GameEngine
{
	enum ENGINE_API ComponentAction
	{
		None = 0,
		Added = 1
	};

	class ENGINE_API ComponentAssignedEvent : public EventBase<ComponentAssignedEvent>
	{
	public:
		//ComponentAssignEvent() : Action(ComponentAction::None), Type(ComponentType::None){}
		ComponentAction Action;
		ComponentType Type;
	};

}

