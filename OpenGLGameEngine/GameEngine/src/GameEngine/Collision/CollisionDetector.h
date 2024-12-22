#pragma once
#include "../Core.h"
#include <unordered_map>
#include "CollisionEnum.h"
#include "../Debugging/Log.h"
#include "../Entities/GameEntity.h"
#include "../Components/ColliderComponent.h"
#include "../StartModeSettings.h"
#include "CollisionData.h"
#include "../Debugging/Log.h"

namespace GameEngine
{
	class ENGINE_API CollisionDetector
	{
	public:
		void ProcessCollisionBuffer();
		void ProcessCollisionData(std::shared_ptr<CollisionData> collisionData);
		void AddCollisionCallback(CollisionState state, std::function<void(std::shared_ptr<CollisionData>)> callback);
		void RemoveCollisionCallback(CollisionState state);
		void ClearCallbacks();
		void RemoveColliderFromCurrentCollisions(std::shared_ptr<ColliderComponent> removedCollider);
		void HandleOnCollisionEnter(std::shared_ptr<CollisionData> collisionData);
		void HandleOnCollisionStay(std::shared_ptr<CollisionData> collisionData);
		void HandleOnCollisionExit(std::shared_ptr<CollisionData> collisionData);
		void AddToProcessBuffer(std::shared_ptr<CollisionData> collisionData);
		void ClearProcessBuffer();
	private:
		std::unordered_map<std::shared_ptr<ColliderComponent>, CollisionState> m_CurrentCollisions;
		std::unordered_map<
			CollisionState,
			std::function<void(std::shared_ptr<CollisionData>)>> m_CollisionCallbacks;
		void updateCollisionState(std::shared_ptr<CollisionData> collisionData, CollisionState state);
		void processOnDetectionSuccess(std::shared_ptr<CollisionData> collisionData);
		void processOnDetectionFailed(std::shared_ptr<CollisionData> collisionData);
		std::vector<std::shared_ptr<CollisionData>> m_CollisionDataBuffer;

		//FOR DEBUG
		const bool IS_LOGS_ACTIVE = false;
	};
}

