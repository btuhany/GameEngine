#pragma once
#include "../Core.h"
namespace GameEngine
{
	enum class ENGINE_API ColliderType
	{
		None = 0,
		BoxCollider2D = 1
	};
	enum class ENGINE_API CollisionType
	{
		Static = 0,
		Dynamic = 1
	};
	enum class ENGINE_API CollisionState
	{
		None = 0,
		Enter = 1,
		Stay = 2,
		Exit = 3
	};
}