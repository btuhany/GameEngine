#include "ColliderComponent.h"
namespace GameEngine
{
	ColliderComponent::ColliderComponent()
	{
		detector = nullptr;
	}
	ColliderComponent::ColliderComponent(std::shared_ptr<CollisionDetector> collisionDetector)
	{
		detector = collisionDetector;
	}
	ComponentType ColliderComponent::getType()
	{
		return ComponentType::Collision;
	}
	ColliderType ColliderComponent::getColliderType()
	{
		return ColliderType::None;
	}
}
