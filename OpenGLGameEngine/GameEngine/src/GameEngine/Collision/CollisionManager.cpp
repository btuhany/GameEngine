#include "CollisionManager.h"
namespace GameEngine
{
	CollisionManager::CollisionManager()
	{
		m_TimeCounter = 0.0f;
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
	void CollisionManager::Update(float deltaTime)
	{
		m_TimeCounter += deltaTime;
		if (m_TimeCounter <= m_UpdateCollisionDuration)
		{
			return;
		}
		m_TimeCounter = 0.0f;

		for (size_t i = 0; i < m_ColliderComponents.size(); i++)
		{
			auto controlledCollider = m_ColliderComponents[i];

			for (size_t j = 0; j < m_ColliderComponents.size(); j++)
			{
				if (i == j)
					continue;

				bool isInBounds = false;
				auto otherCollider = m_ColliderComponents[j];
				if (controlledCollider->getColliderType() == ColliderType::BoxCollider2D)
				{
					if (otherCollider->getColliderType() == ColliderType::BoxCollider2D)
					{
						auto controlledBoxCollider = std::static_pointer_cast<BoxCollider2DComponent>(controlledCollider);
						auto otherBoxCollider = std::static_pointer_cast<BoxCollider2DComponent>(otherCollider);
						isInBounds = AreBoxCollidersCollide(controlledBoxCollider, otherBoxCollider);
					}
				}

				if (controlledCollider->detector != nullptr)
				{
					controlledCollider->detector->ProcessCollisionResult(isInBounds, otherCollider);
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
	bool CollisionManager::AreBoxCollidersCollide(std::shared_ptr<BoxCollider2DComponent> boxColliderA, std::shared_ptr<BoxCollider2DComponent> boxColliderB)
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
		for (size_t i = 0; i < 4; i++)
		{
			auto node = boundsB[i];
			if (boundsA[(int)BoxColliderPosTypes::TopRight].x > node.x
				&& node.x > boundsA[(int)BoxColliderPosTypes::BottomLeft].x)
			{
				if (boundsA[(int)BoxColliderPosTypes::TopRight].y > node.y
					&& node.y > boundsA[(int)BoxColliderPosTypes::BottomLeft].y)
				{
					//printf("\n Collision! node: %d", i);
					return true;
				}
			}
		}
		return false;
	}
}
