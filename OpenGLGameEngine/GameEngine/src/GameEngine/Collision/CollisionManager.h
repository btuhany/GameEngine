#pragma once
#include "../Core.h"
#include "CollisionEnum.h"
#include "../Event/EventManager.h"
#include "../Event/ComponentEvent.h"
#include "../Components/ColliderComponent.h"
#include "../Components/BoxCollider2DComponent.h"
#include "../Collision/CollisionDetector.h"
namespace GameEngine
{
	class ENGINE_API CollisionManager
	{
	public:
		CollisionManager();
		~CollisionManager();
		void Update(float deltaTime);
	private:
		void onComponentEvent(std::shared_ptr<ComponentEvent> componentEvent);
		std::vector<std::shared_ptr<ComponentEvent>> m_ComponentEventProcessBufferList;
		std::vector<std::shared_ptr<ColliderComponent>> m_ColliderComponents;
		bool AreBoxCollidersCollide(std::shared_ptr<BoxCollider2DComponent> boxColliderA, std::shared_ptr<BoxCollider2DComponent> boxColliderB);
		float m_TimeCounter = 0.0f;
		const float m_UpdateCollisionDuration = 0.2f;
	};
}

