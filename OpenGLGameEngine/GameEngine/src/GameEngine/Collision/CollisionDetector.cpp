#include "CollisionDetector.h"
namespace GameEngine
{
	void CollisionDetector::HandleOnCollisionDetected(std::shared_ptr<ColliderComponent> detectedCollider)
	{
		//if (detectedCollider.expired())
		//{
		//	LOG_CORE_ERROR("HandleOnCollisionDetected | detected collider has expired");
		//	return;
		//}
		//auto collider = detectedCollider.lock();
		//if (collider->getEntity().expired())
		//{
		//	LOG_CORE_ERROR("HandleOnCollisionDetected | detected collider owner entity has expired");
		//	return;
		//}
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

	void CollisionDetector::HandleOnCollisionNotDetected(std::shared_ptr<ColliderComponent> detectedCollider)
	{
		//if (detectedCollider.expired())
		//{
		//	LOG_CORE_ERROR("HandleOnCollisionDetected | detected collider has expired");
		//	return;
		//}
		//auto collider = detectedCollider.lock();
		//if (collider->getEntity().expired())
		//{
		//	LOG_CORE_ERROR("HandleOnCollisionDetected | detected collider owner entity has expired");
		//	return;
		//}
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

	void CollisionDetector::HandleOnCollisionEnter(std::shared_ptr<ColliderComponent> otherCollider)
	{
		auto gameEntityName = otherCollider->getEntity().lock()->getName();
		std::cout << "HandleOnCollision Enter with: " << gameEntityName << std::endl;
	}

	void CollisionDetector::HandleOnCollisionStay(std::shared_ptr<ColliderComponent> otherCollider)
	{
		auto gameEntityName = otherCollider->getEntity().lock()->getName();
		std::cout << "HandleOnCollision Stay with: " << gameEntityName << std::endl;
	}

	void CollisionDetector::HandleOnCollisionExit(std::shared_ptr<ColliderComponent> otherCollider)
	{
		auto gameEntityName = otherCollider->getEntity().lock()->getName();
		std::cout << "HandleOnCollision Exit with: " << gameEntityName << std::endl;
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
