#include "ColliderComponent.h"
namespace GameEngine
{
	ColliderComponent::ColliderComponent()
	{
		m_CollisionState = CollisionState::None;
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
