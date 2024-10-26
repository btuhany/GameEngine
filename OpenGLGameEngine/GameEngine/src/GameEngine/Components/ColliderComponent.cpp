#include "ColliderComponent.h"
namespace GameEngine
{
	ComponentType ColliderComponent::getType()
	{
		return ComponentType::Collision;
	}
}
