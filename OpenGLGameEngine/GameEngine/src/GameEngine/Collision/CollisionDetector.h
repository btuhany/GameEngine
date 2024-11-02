#pragma once
#include "../Core.h"
#include <unordered_map>
#include "CollisionEnum.h"
#include "../Debugging/Log.h"
#include "../Entities/GameEntity.h"
#include "../Components/ColliderComponent.h"
#include "../StartModeSettings.h"

namespace GameEngine
{
	class ENGINE_API CollisionDetector
	{
	public:
		void ProcessCollisionResult(bool isCollided, std::shared_ptr<ColliderComponent> otherCollider);
		void AddCollisionCallback(CollisionState state, std::function<void(std::shared_ptr<ColliderComponent>)> callback);
		void RemoveCollisionCallback(CollisionState state);
		void ClearCallbacks();
		void RemoveColliderFromCurrentCollisions(std::shared_ptr<ColliderComponent> removedCollider);
		void HandleOnCollisionEnter(std::shared_ptr<ColliderComponent> otherCollider);
		void HandleOnCollisionStay(std::shared_ptr<ColliderComponent> otherCollider);
		void HandleOnCollisionExit(std::shared_ptr<ColliderComponent> otherCollider);
	private:
		std::unordered_map<std::shared_ptr<ColliderComponent>, CollisionState> m_CurrentCollisions;
		std::unordered_map<
			CollisionState,
			std::function<void(std::shared_ptr<ColliderComponent>)>> m_CollisionCallbacks;
		void updateCollisionState(std::shared_ptr<ColliderComponent> collider, CollisionState state);
		void processOnDetectionSuccess(std::shared_ptr<ColliderComponent> detectedCollider);
		void processOnDetectionFailed(std::shared_ptr<ColliderComponent> detectedCollider);
	};
}

