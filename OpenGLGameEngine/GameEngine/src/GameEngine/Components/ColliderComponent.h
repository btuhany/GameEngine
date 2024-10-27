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
	enum class CollisionState
	{
		None = 0,
		Enter = 1,
		Stay = 2,
		Exit = 3
	};
	class ENGINE_API ColliderComponent : public Component
	{
	public:
		ColliderComponent();
		ComponentType getType() override;
		void setCollisionState(CollisionState state);
		CollisionState getCollisionState();
		virtual ColliderType getColliderType() = 0;
	protected:
		CollisionState m_CollisionState;
	};
}

