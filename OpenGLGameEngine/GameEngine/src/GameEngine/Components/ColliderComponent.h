#pragma once
#include "../Core.h"
#include "../Collision/CollisionEnum.h"
#include "Component.h"
#include "../Math/Vector3.h"
namespace GameEngine
{
	class CollisionDetector;
	class ENGINE_API ColliderComponent : public Component
	{
	public:
		ColliderComponent();
		ColliderComponent(std::shared_ptr<CollisionDetector> collisionDetector);
		ComponentType getType() override;
		virtual ColliderType getColliderType();
		std::shared_ptr<CollisionDetector> detector;

	};
}

