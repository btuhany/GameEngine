#pragma once
#include "../Core.h"
#include "../Math/Vector3.h"
namespace GameEngine
{
	class ENGINE_API CollisionData
	{
	public:
		bool isInBounds;
		Vector3 collidedNodePos; //TODO detect all nodes collided
		std::shared_ptr<ColliderComponent> otherCollider;
		CollisionData()	: isInBounds(false), collidedNodePos(0.0f, 0.0f, 0.0f), otherCollider(nullptr) {}
	};
}