#include "CollisionDetector.h"
namespace GameEngine
{
	void CollisionDetector::processOnDetectionSuccess(std::shared_ptr<ColliderComponent> detectedCollider)
	{
		auto it = m_CurrentCollisions.find(detectedCollider);
		if (it != m_CurrentCollisions.end())
		{
			auto currentState = it->second;
			switch (currentState)
			{
			case GameEngine::CollisionState::None:
				updateCollisionState(detectedCollider, CollisionState::Enter);
				break;
			case GameEngine::CollisionState::Enter:
				updateCollisionState(detectedCollider, CollisionState::Stay);
				break;
			case GameEngine::CollisionState::Stay:
				updateCollisionState(detectedCollider, CollisionState::Stay);
				break;
			case GameEngine::CollisionState::Exit:
				updateCollisionState(detectedCollider, CollisionState::Enter);
				break;
			default:
				break;
			}

		}
		else
		{
			updateCollisionState(detectedCollider, CollisionState::Enter);
		}
	}

	void CollisionDetector::processOnDetectionFailed(std::shared_ptr<ColliderComponent> detectedCollider)
	{
		auto it = m_CurrentCollisions.find(detectedCollider);
		if (it != m_CurrentCollisions.end())
		{
			auto currentState = it->second;
			switch (currentState)
			{
			case GameEngine::CollisionState::None:
				LOG_CORE_ERROR("Collision listener logic error! | None");
				updateCollisionState(detectedCollider, CollisionState::None);
				break;
			case GameEngine::CollisionState::Enter:
				updateCollisionState(detectedCollider, CollisionState::Exit);
				break;
			case GameEngine::CollisionState::Stay:
				updateCollisionState(detectedCollider, CollisionState::Exit);
				break;
			case GameEngine::CollisionState::Exit:
				updateCollisionState(detectedCollider, CollisionState::None);
				break;
			default:
				break;
			}
		}
	}

	void CollisionDetector::ProcessCollisionResult(bool isCollided, std::shared_ptr<ColliderComponent> otherCollider)
	{
		if (isCollided)
			processOnDetectionSuccess(otherCollider);
		else
			processOnDetectionFailed(otherCollider);
	}

	void CollisionDetector::AddCollisionCallback(CollisionState state, std::function<void(std::shared_ptr<ColliderComponent>)> callback)
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

	void CollisionDetector::HandleOnCollisionEnter(std::shared_ptr<ColliderComponent> otherCollider)
	{
		if (SETTINGS_COLLIDER_DEBUG_MODE)
		{
			auto gameEntityName = otherCollider->getEntity().lock()->getName();
			std::cout << "HandleOnCollision Enter with: " << gameEntityName << std::endl;
		}
		auto it = m_CollisionCallbacks.find(CollisionState::Enter);
		if (it != m_CollisionCallbacks.end() && it->second)
		{
			it->second(otherCollider);
		}
	}

	void CollisionDetector::HandleOnCollisionStay(std::shared_ptr<ColliderComponent> otherCollider)
	{
		if (SETTINGS_COLLIDER_DEBUG_MODE)
		{
			auto gameEntityName = otherCollider->getEntity().lock()->getName();
			std::cout << "HandleOnCollision Stay with: " << gameEntityName << std::endl;
		}
		auto it = m_CollisionCallbacks.find(CollisionState::Stay);
		if (it != m_CollisionCallbacks.end() && it->second)
		{
			it->second(otherCollider);
		}
	}

	void CollisionDetector::HandleOnCollisionExit(std::shared_ptr<ColliderComponent> otherCollider)
	{
		if (SETTINGS_COLLIDER_DEBUG_MODE)
		{
			auto gameEntityName = otherCollider->getEntity().lock()->getName();
			std::cout << "HandleOnCollision Exit with: " << gameEntityName << std::endl;
		}
		auto it = m_CollisionCallbacks.find(CollisionState::Exit);
		if (it != m_CollisionCallbacks.end() && it->second)
		{
			it->second(otherCollider);
		}
	}

	void CollisionDetector::updateCollisionState(std::shared_ptr<ColliderComponent> collider, CollisionState state)
	{
		m_CurrentCollisions[collider] = state;
		switch (state)
		{
		case GameEngine::CollisionState::None:
			m_CurrentCollisions.erase(collider);
			break;
		case GameEngine::CollisionState::Enter:
			HandleOnCollisionEnter(collider);
			break;
		case GameEngine::CollisionState::Stay:
			HandleOnCollisionStay(collider);
			break;
		case GameEngine::CollisionState::Exit:
			HandleOnCollisionExit(collider);
			break;
		default:
			break;
		}
	}
	
}
