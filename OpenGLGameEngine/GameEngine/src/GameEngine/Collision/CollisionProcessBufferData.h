#pragma once
#pragma once
#include "../Core.h"
#include "../Components/ColliderComponent.h"
namespace GameEngine
{
	class ENGINE_API CollisionProcessBufferData
	{
	public:
		std::shared_ptr<ColliderComponent> collider;
		std::shared_ptr<CollisionData> collisionData;
		CollisionState state;
	};
}