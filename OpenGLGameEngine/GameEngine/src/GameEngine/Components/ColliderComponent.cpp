#include "ColliderComponent.h"
namespace GameEngine
{
	ColliderComponent::ColliderComponent(CollisionType collisionType)
	{
		m_CollisionType = collisionType;
		detector = nullptr;
	}
	ColliderComponent::ColliderComponent(CollisionType collisionType, std::shared_ptr<CollisionDetector> collisionDetector)
	{
		detector = collisionDetector;
		m_CollisionType = collisionType;
	}
	ComponentType ColliderComponent::getType()
	{
		return ComponentType::Collision;
	}
	ColliderType ColliderComponent::getColliderType()
	{
		return ColliderType::None;
	}
	CollisionType ColliderComponent::getCollisionType()
	{
		return m_CollisionType;
	}
}
