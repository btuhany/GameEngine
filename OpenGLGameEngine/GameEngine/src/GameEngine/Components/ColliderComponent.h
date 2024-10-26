#pragma once
#include "Core.h"
#include "Component.h"
#include "../Math/Vector3.h"
namespace GameEngine
{
	enum class ColliderType
	{
		BoxCollider2D = 0
	};
	class ENGINE_API ColliderComponent : public Component
	{
	public:
		ComponentType getType() override;
		virtual ColliderType getColliderType() = 0;
	};
}

