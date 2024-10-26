#include "ColliderComponent.h"
namespace GameEngine
{
	ColliderComponent::ColliderComponent()
	{
	}
	void ColliderComponent::setCollisionType(CollisionType collisionType)
	{
		m_CollisionType = collisionType;
	}
	CollisionType ColliderComponent::getCollisionType()
	{
		return m_CollisionType;
	}
	ComponentType ColliderComponent::getType()
	{
		return ComponentType::Collision;
	}
}
