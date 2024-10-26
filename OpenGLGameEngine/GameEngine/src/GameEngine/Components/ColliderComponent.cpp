#include "ColliderComponent.h"
namespace GameEngine
{
	ColliderComponent::ColliderComponent()
	{
		m_CollisionState = CollisionState::None;
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
	void ColliderComponent::setCollisionState(CollisionState state)
	{
		printf("\n Collision state: %d", (int)state);
		m_CollisionState = state;
	}
	CollisionState ColliderComponent::getCollisionState()
	{
		return m_CollisionState;
	}
}
