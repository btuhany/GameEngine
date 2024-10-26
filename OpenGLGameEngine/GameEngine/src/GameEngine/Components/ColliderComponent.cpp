#include "ColliderComponent.h"
namespace GameEngine
{
	ColliderComponent::ColliderComponent()
	{
	}
	ComponentType ColliderComponent::getType()
	{
		return ComponentType::Collision;
	}
}
