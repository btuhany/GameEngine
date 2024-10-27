#pragma once
#include "../Core.h"
#include "CollisionEnum.h"
#include "../Debugging/Log.h"
#include "../Entities/GameEntity.h"
#include "../Components/ColliderComponent.h"

namespace GameEngine
{
	class ENGINE_API CollisionDetector
	{
	public:
		void HandleOnCollisionDetected(std::shared_ptr<ColliderComponent> detectedCollider);
		void HandleOnCollisionNotDetected(std::shared_ptr<ColliderComponent> detectedCollider);
		void HandleOnCollisionEnter(std::shared_ptr<ColliderComponent> otherCollider);
		void HandleOnCollisionStay(std::shared_ptr<ColliderComponent> otherCollider);
		void HandleOnCollisionExit(std::shared_ptr<ColliderComponent> otherCollider);
	private:
		std::unordered_map<std::shared_ptr<ColliderComponent>, CollisionState> m_CurrentCollisions;
		void updateCollisionState(std::shared_ptr<ColliderComponent> collider, CollisionState state);
	};
}

