#pragma once
#include "Core.h"
#include "Event/EventManager.h"
#include "Event/ComponentEvent.h"
#include "Components/ColliderComponent.h"
namespace GameEngine
{
	class ENGINE_API CollisionManager
	{
	public:
		CollisionManager();
		~CollisionManager();
	private:
		void onComponentEvent(std::shared_ptr<ComponentEvent> componentEvent);
		std::vector<std::shared_ptr<ColliderComponent>> m_ColliderComponents;
	};
}

