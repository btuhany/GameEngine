#pragma once
#include "../Core.h"
#include "../Math/Vector3.h"
namespace GameEngine
{
	class ENGINE_API CollisionData
	{
	public:
		bool isInBounds;  //TODO unnecessary bool
		std::vector<Vector3> collidedNodePosList;
		std::shared_ptr<ColliderComponent> otherCollider;
		CollisionData()	: isInBounds(false), collidedNodePosList(std::vector<Vector3>()), otherCollider(nullptr) {}
	};
}