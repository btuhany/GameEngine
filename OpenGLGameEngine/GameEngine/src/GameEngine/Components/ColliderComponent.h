#pragma once
#include "Core.h"
#include "Component.h"
namespace GameEngine
{
	class ENGINE_API ColliderComponent : Component
	{
	public:
		ComponentType getType() override;
	};
}

