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

	void CollisionDetector::ProcessCollisionBuffer()
	{
		for (size_t i = 0; i < m_CollisionDataBuffer.size(); i++)
		{
			auto& collisionData = m_CollisionDataBuffer[i];
			if (collisionData->isInBounds)
				processOnDetectionSuccess(collisionData);
			else
				processOnDetectionFailed(collisionData);
		}

		processCollisionResultBuffer();
	}

	void CollisionDetector::ProcessCollisionData(std::shared_ptr<CollisionData> collisionData)
	{
		//Instant call
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

	void CollisionDetector::AddToProcessBuffer(std::shared_ptr<CollisionData> collisionData)
	{
		m_CollisionDataBuffer.push_back(collisionData);
	}

	void CollisionDetector::ClearProcessBuffer()
	{
		m_CollisionDataBuffer.clear();
	}

	void CollisionDetector::updateCollisionState(std::shared_ptr<CollisionData> collisionData, CollisionState state)
	{
		auto otherCollider = collisionData->otherCollider;
		m_CurrentCollisions[otherCollider] = state;
		if (state == CollisionState::None)
		{
			m_CurrentCollisions.erase(otherCollider);
		}
		bufferCollisionResult(collisionData, state);
	}

	void CollisionDetector::bufferCollisionResult(std::shared_ptr<CollisionData> collisionData, CollisionState state)
	{
		auto bufferData = std::make_shared<CollisionProcessBufferData>();
		bufferData->collider = collisionData->otherCollider;
		bufferData->collisionData = collisionData;
		bufferData->state = state;

		m_CollisionProcessBuffer.push_back(bufferData);
	}

	void CollisionDetector::processCollisionResultBuffer()
	{
		for (size_t i = 0; i < m_CollisionProcessBuffer.size(); i++)
		{
			auto state = m_CollisionProcessBuffer[i]->state;
			switch (state)
			{
			case GameEngine::CollisionState::Enter:
				HandleOnCollisionEnter(m_CollisionProcessBuffer[i]->collisionData);
				break;
			case GameEngine::CollisionState::Stay:
				HandleOnCollisionStay(m_CollisionProcessBuffer[i]->collisionData);
				break;
			case GameEngine::CollisionState::Exit:
				HandleOnCollisionExit(m_CollisionProcessBuffer[i]->collisionData);
				break;
			default:
				break;
			}
		}
		m_CollisionProcessBuffer.clear();
	}
	
}
