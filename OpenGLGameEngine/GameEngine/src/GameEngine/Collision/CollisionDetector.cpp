#include "CollisionDetector.h"
namespace GameEngine
{
	void CollisionDetector::processOnDetectionSuccess(std::shared_ptr<CollisionData> collisionData)
	{
		auto detectedCollider = collisionData->otherCollider;
		auto it = m_CurrentCollisions.find(detectedCollider);
		if (it != m_CurrentCollisions.end())
		{
			auto currentState = it->second;
			switch (currentState)
			{
			case GameEngine::CollisionState::None:
				updateCollisionState(collisionData, CollisionState::Enter);
				break;
			case GameEngine::CollisionState::Enter:
				updateCollisionState(collisionData, CollisionState::Stay);
				break;
			case GameEngine::CollisionState::Stay:
				updateCollisionState(collisionData, CollisionState::Stay);
				break;
			case GameEngine::CollisionState::Exit:
				updateCollisionState(collisionData, CollisionState::Enter);
				break;
			default:
				break;
			}

		}
		else
		{
			updateCollisionState(collisionData, CollisionState::Enter);
		}
	}

	void CollisionDetector::processOnDetectionFailed(std::shared_ptr<CollisionData> collisionData)
	{
		auto detectedCollider = collisionData->otherCollider;
		auto it = m_CurrentCollisions.find(detectedCollider);
		if (it != m_CurrentCollisions.end())
		{
			auto currentState = it->second;
			switch (currentState)
			{
			case GameEngine::CollisionState::None:
				if (IS_LOGS_ACTIVE)
					LOG_CORE_ERROR("Collision listener logic error! | None");
				updateCollisionState(collisionData, CollisionState::None);
				break;
			case GameEngine::CollisionState::Enter:
				updateCollisionState(collisionData, CollisionState::Exit);
				break;
			case GameEngine::CollisionState::Stay:
				updateCollisionState(collisionData, CollisionState::Exit);
				break;
			case GameEngine::CollisionState::Exit:
				updateCollisionState(collisionData, CollisionState::None);
				break;
			default:
				break;
			}
		}
	}

	void CollisionDetector::ProcessCollisionResult(std::shared_ptr<CollisionData> collisionData)
	{
		if (collisionData->isInBounds)
			processOnDetectionSuccess(collisionData);
		else
			processOnDetectionFailed(collisionData);
	}

	void CollisionDetector::AddCollisionCallback(CollisionState state, std::function<void(std::shared_ptr<CollisionData>)> callback)
	{
		m_CollisionCallbacks[state] = callback;
	}

	void CollisionDetector::RemoveCollisionCallback(CollisionState state)
	{
		m_CollisionCallbacks.erase(state);
	}

	void CollisionDetector::ClearCallbacks()
	{
		m_CollisionCallbacks.clear();
	}

	void CollisionDetector::RemoveColliderFromCurrentCollisions(std::shared_ptr<ColliderComponent> removedCollider)
	{
		auto it = m_CurrentCollisions.find(removedCollider);
		if (it != m_CurrentCollisions.end())
			m_CurrentCollisions.erase(removedCollider);
	}

	void CollisionDetector::HandleOnCollisionEnter(std::shared_ptr<CollisionData> collisionData)
	{
		auto otherCollider = collisionData->otherCollider;
		if (SETTINGS_COLLIDER_DEBUG_MODE)
		{
			auto gameEntityName = otherCollider->getEntity().lock()->getName();
			if (IS_LOGS_ACTIVE)
				LOG_CORE_INFO("HandleOnCollision Enter with: " + gameEntityName);
		}
		auto it = m_CollisionCallbacks.find(CollisionState::Enter);
		if (it != m_CollisionCallbacks.end() && it->second)
		{
			it->second(collisionData);
		}
	}

	void CollisionDetector::HandleOnCollisionStay(std::shared_ptr<CollisionData> collisionData)
	{
		auto otherCollider = collisionData->otherCollider;
		if (SETTINGS_COLLIDER_DEBUG_MODE)
		{
			auto gameEntityName = otherCollider->getEntity().lock()->getName();
			//std::cout << "HandleOnCollision Stay with: " << gameEntityName << std::endl;
		}
		auto it = m_CollisionCallbacks.find(CollisionState::Stay);
		if (it != m_CollisionCallbacks.end() && it->second)
		{
			it->second(collisionData);
		}
	}

	void CollisionDetector::HandleOnCollisionExit(std::shared_ptr<CollisionData> collisionData)
	{
		auto otherCollider = collisionData->otherCollider;
		if (SETTINGS_COLLIDER_DEBUG_MODE)
		{
			auto gameEntityName = otherCollider->getEntity().lock()->getName();
			if (IS_LOGS_ACTIVE)
				LOG_CORE_INFO("HandleOnCollision Exit with: " + gameEntityName);
		}
		auto it = m_CollisionCallbacks.find(CollisionState::Exit);
		if (it != m_CollisionCallbacks.end() && it->second)
		{
			it->second(collisionData);
		}
	}

	void CollisionDetector::updateCollisionState(std::shared_ptr<CollisionData> collisionData, CollisionState state)
	{
		auto otherCollider = collisionData->otherCollider;
		m_CurrentCollisions[otherCollider] = state;
		switch (state)
		{
		case GameEngine::CollisionState::None:
			m_CurrentCollisions.erase(otherCollider);
			break;
		case GameEngine::CollisionState::Enter:
			HandleOnCollisionEnter(collisionData);
			break;
		case GameEngine::CollisionState::Stay:
			HandleOnCollisionStay(collisionData);
			break;
		case GameEngine::CollisionState::Exit:
			HandleOnCollisionExit(collisionData);
			break;
		default:
			break;
		}
	}
	
}
