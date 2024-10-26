#pragma once
#include <array>
#include "../Core.h"
#include "ColliderComponent.h"
#include "../Debugging/Log.h"
#include "../Entities/GameEntity.h"
#include "../Math/Vector2.h"
namespace GameEngine
{
	enum class BoxColliderPosTypes
	{
		TopLeft = 0,
		TopRight = 1,
		BottomRight = 2,
		BottomLeft = 3
	};
	class ENGINE_API BoxCollider2DComponent : public ColliderComponent
	{
	public:
		float getWidth();
		float getHeight();
		std::array<Vector2, 4> getBoundNodes();
		ColliderType getColliderType() override;
	private:
		float m_Width;
		float m_Height;
	};
}

