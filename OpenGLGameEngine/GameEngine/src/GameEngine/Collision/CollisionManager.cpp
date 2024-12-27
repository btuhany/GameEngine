#include "CollisionManager.h"
namespace GameEngine
{
	CollisionManager::CollisionManager()
	{
		m_TimeCounter = 0.0f;
		EventManager::GetInstance().Subscribe<ComponentEvent>(
			[this](std::shared_ptr<ComponentEvent> event) {
				m_ComponentEventProcessBufferList.push_back(event);
			}, 10);
	}

	CollisionManager::~CollisionManager()
	{
		EventManager::GetInstance().Unsubscribe<ComponentEvent>(
			[this](std::shared_ptr<ComponentEvent> event) {
				m_ComponentEventProcessBufferList.push_back(event);
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

		//DETECT COLLISIONS
		for (size_t i = 0; i < m_ColliderComponents.size(); i++)
		{
			if (!isAbleToCollide(m_ColliderComponents[i]))
				continue;

			auto controlledCollider = m_ColliderComponents[i];
			if (controlledCollider->getCollisionType() != CollisionType::Dynamic)
				continue;

			
			for (size_t j = 0; j < m_ColliderComponents.size(); j++)
			{
				if (!isAbleToCollide(m_ColliderComponents[j]))
					continue;

				if (i == j)
					continue;

				auto otherCollider = m_ColliderComponents[j];
				auto collisionData = std::shared_ptr<CollisionData>();
				if (controlledCollider->getColliderType() == ColliderType::BoxCollider2D)
				{
					auto controlledBoxCollider = std::static_pointer_cast<BoxCollider2DComponent>(controlledCollider);

					if (otherCollider->getColliderType() == ColliderType::BoxCollider2D)
					{
						auto otherBoxCollider = std::static_pointer_cast<BoxCollider2DComponent>(otherCollider);
						collisionData = AreBoxCollidersCollide(controlledBoxCollider, otherBoxCollider);
					}
				}

				if (controlledCollider->detector != nullptr)
				{
					controlledCollider->detector->AddToProcessBuffer(collisionData);
				}
			}
		}


		//PROCESSING COLLISION DATA IN BUFFER
		for (size_t i = 0; i < m_ColliderComponents.size(); i++)
		{
			auto colliderComp = m_ColliderComponents[i];
			if (colliderComp->detector != nullptr)
			{
				colliderComp->detector->ProcessCollisionBuffer();
				colliderComp->detector->ClearProcessBuffer();
			}
		}

		//processing component events after update, in case of deactivating or destroying objects in collision events
		for (size_t i = 0; i < m_ComponentEventProcessBufferList.size(); i++)
		{
			auto compEventData = m_ComponentEventProcessBufferList[i];
			onComponentEvent(compEventData);
		}
		m_ComponentEventProcessBufferList.clear();
	}
	void CollisionManager::onComponentEvent(std::shared_ptr<ComponentEvent> componentEvent)
	{
		auto componentType = componentEvent->comp->getType();
		auto compAction = componentEvent->compAction;
		if (componentType == ComponentType::Collision)
		{
			if (compAction == ComponentAction::Added || compAction == ComponentAction::OwnerEnabled)
			{
				auto colliderComp = std::static_pointer_cast<ColliderComponent>(componentEvent->comp);
				auto it = std::find(m_ColliderComponents.begin(), m_ColliderComponents.end(), colliderComp);
				if (it == m_ColliderComponents.end())
				{
					m_ColliderComponents.push_back(colliderComp);
				}
			}
			else if (compAction == ComponentAction::OwnerPreDestroyed || compAction == ComponentAction::OwnerDisabled)
			{
				auto colliderComp = std::static_pointer_cast<ColliderComponent>(componentEvent->comp);
				auto it = std::find(m_ColliderComponents.begin(), m_ColliderComponents.end(), colliderComp);
				if (it != m_ColliderComponents.end())
				{
					m_ColliderComponents.erase(it);
				}

				for (size_t i = 0; i < m_ColliderComponents.size(); i++)
				{
					auto controlledCollider = m_ColliderComponents[i];
					if (controlledCollider->getCollisionType() == CollisionType::Dynamic)
					{
						if (controlledCollider->detector != nullptr)
						{
							auto collisionData = std::make_shared<CollisionData>();
							collisionData->isInBounds = false;
							collisionData->collidedNodePosList = std::vector<Vector3>();
							collisionData->otherCollider = colliderComp;
							controlledCollider->detector->ProcessCollisionData(collisionData);
							controlledCollider->detector->RemoveColliderFromCurrentCollisions(colliderComp); 	//not sure if this function should be called
						}
					}
				}
			}
		}
	}
	bool CollisionManager::isAbleToCollide(std::shared_ptr<ColliderComponent> collider)
	{
		if (collider->getEntity().expired())
			return false;

		auto ownerEntity = collider->getEntity().lock();
		return ownerEntity->IsActive() && collider->getEnabled();
	}
	std::shared_ptr<CollisionData> CollisionManager::AreBoxCollidersCollide(std::shared_ptr<BoxCollider2DComponent> controlledCollider, std::shared_ptr<BoxCollider2DComponent> otherCollider)
	{
		auto collisionData = std::make_shared<CollisionData>();
		collisionData->isInBounds = false;
		collisionData->collidedNodePosList = std::vector<Vector3>();
		collisionData->otherCollider = otherCollider;

		if (controlledCollider->getEntity().expired() || otherCollider->getEntity().expired())
		{

			return collisionData;
		}

		auto boundsA = controlledCollider->getBoundNodes();
		auto boundsB = otherCollider->getBoundNodes();


		//TODO could be more optimized but i dont care for optimization for now, its better for the code readability.

		for (size_t i = 0; i < 4; i++)
		{
			auto node = boundsA[i];
			if (boundsB[(int)BoxColliderPosType::TopRight].x >= node.x 
				&& node.x >= boundsB[(int)BoxColliderPosType::BottomLeft].x) 
			{
				if (boundsB[(int)BoxColliderPosType::TopRight].y >= node.y 
					&& node.y >= boundsB[(int)BoxColliderPosType::BottomLeft].y)
				{
					collisionData->collidedNodePosList.push_back(Vector3(node.x, node.y, 0.0f));
				}
			}
		}
		for (size_t i = 0; i < 4; i++)
		{
			auto node = boundsB[i];
			if (boundsA[(int)BoxColliderPosType::TopRight].x >= node.x
				&& node.x >= boundsA[(int)BoxColliderPosType::BottomLeft].x)
			{
				if (boundsA[(int)BoxColliderPosType::TopRight].y >= node.y
					&& node.y >= boundsA[(int)BoxColliderPosType::BottomLeft].y)
				{
					collisionData->collidedNodePosList.push_back(Vector3(node.x, node.y, 0.0f));
				}
			}
		}

		if (collisionData->collidedNodePosList.size() > 0)
		{
			collisionData->isInBounds = true;
		}

		return collisionData;
	}
}
