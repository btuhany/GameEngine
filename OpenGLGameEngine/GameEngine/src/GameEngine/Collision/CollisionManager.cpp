#include "CollisionManager.h"
namespace GameEngine
{
	CollisionManager::CollisionManager()
	{
		EventManager::GetInstance().Subscribe<ComponentEvent>(
			[this](std::shared_ptr<ComponentEvent> event) {
				this->onComponentEvent(event);
			}, 10);
	}

	CollisionManager::~CollisionManager()
	{
		EventManager::GetInstance().Unsubscribe<ComponentEvent>(
			[this](std::shared_ptr<ComponentEvent> event) {
				this->onComponentEvent(event);
			});
	}
	void CollisionManager::Tick()
	{
		for (size_t i = 0; i < m_ColliderComponents.size(); i++)
		{
			auto dynamicCollider = m_ColliderComponents[i];

			bool isInBounds = false;
			for (size_t j = 0; j < m_ColliderComponents.size(); j++)
			{
				if (i == j)
					continue;

				auto otherCollider = m_ColliderComponents[j];
				if (dynamicCollider->getColliderType() == ColliderType::BoxCollider2D)
				{
					if (otherCollider->getColliderType() == ColliderType::BoxCollider2D)
					{
						auto boxColliderComponentA = std::static_pointer_cast<BoxCollider2DComponent>(dynamicCollider);
						auto boxColliderComponentB = std::static_pointer_cast<BoxCollider2DComponent>(otherCollider);
						isInBounds = checkBounds(boxColliderComponentA, boxColliderComponentB);
					}
				}
			}

			auto collisionState = dynamicCollider->getCollisionState();
			if (isInBounds)
			{
				switch (collisionState)
				{
					case GameEngine::CollisionState::None:
						dynamicCollider->setCollisionState(CollisionState::Enter);
						break;
					case GameEngine::CollisionState::Enter:
						dynamicCollider->setCollisionState(CollisionState::Stay);
						break;
					case GameEngine::CollisionState::Stay:
						printf("Collision stay \n");
						break;
					case GameEngine::CollisionState::Exit:
						dynamicCollider->setCollisionState(CollisionState::Enter);
						break;
					default:
						break;
				}
			}
			else
			{
				switch (collisionState)
				{
				case GameEngine::CollisionState::Enter:
				case GameEngine::CollisionState::Stay:
					dynamicCollider->setCollisionState(CollisionState::Exit);
					break;
				case GameEngine::CollisionState::Exit:
					dynamicCollider->setCollisionState(CollisionState::None);
					break;
				default:
					break;
				}
			}
		}
	}
	void CollisionManager::onComponentEvent(std::shared_ptr<ComponentEvent> componentEvent)
	{
		if (componentEvent->compAction == ComponentAction::Added)
		{
			auto componentType = componentEvent->comp->getType();
			if (componentType == ComponentType::Collision)
			{
				auto colliderComp = std::static_pointer_cast<ColliderComponent>(componentEvent->comp);
				m_ColliderComponents.push_back(colliderComp);
			}
		}
	}
	bool CollisionManager::checkBounds(std::shared_ptr<BoxCollider2DComponent> boxColliderA, std::shared_ptr<BoxCollider2DComponent> boxColliderB)
	{
		if (boxColliderA->getEntity().expired() || boxColliderB->getEntity().expired())
		{
			return false;
		}

		auto boundsA = boxColliderA->getBoundNodes();
		auto boundsB = boxColliderB->getBoundNodes();

		for (size_t i = 0; i < 4; i++)
		{
			auto node = boundsA[i];
			if (boundsB[(int)BoxColliderPosTypes::TopRight].x > node.x 
				&& node.x > boundsB[(int)BoxColliderPosTypes::BottomLeft].x) 
			{
				if (boundsB[(int)BoxColliderPosTypes::TopRight].y > node.y 
					&& node.y > boundsB[(int)BoxColliderPosTypes::BottomLeft].y)
				{
					//printf("\n Collision! node: %d", i);
					return true;
				}
			}
		}
		return false;
	}
}
