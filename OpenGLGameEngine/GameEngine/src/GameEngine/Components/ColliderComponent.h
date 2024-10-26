#pragma once
#include "../Core.h"
#include "Component.h"
#include "../Math/Vector3.h"
namespace GameEngine
{
	enum class ColliderType
	{
		BoxCollider2D = 0
	};
	enum class CollisionType
	{
		Static = 0,
		Dynamic = 1
	};
	class ENGINE_API ColliderComponent : public Component
	{
	public:
		ColliderComponent();
		void setCollisionType(CollisionType collisionType);
		CollisionType getCollisionType();
		ComponentType getType() override;
		virtual ColliderType getColliderType() = 0;
	protected:
		CollisionType m_CollisionType;
	};
}

