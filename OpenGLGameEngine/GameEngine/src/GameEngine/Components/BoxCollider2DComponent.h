#pragma once
#include <array>
#include "../Core.h"
#include "ColliderComponent.h"
#include "../Debugging/Log.h"
#include "../Entities/GameEntity.h"
#include "../Math/Vector2.h"
#include "../Resource/MeshData.h"
#include "../Resource/Shader.h"
#include "../Render/Renderer.h"
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
		BoxCollider2DComponent(float width, float height, CollisionType collisionType);
		BoxCollider2DComponent(float width, float height, CollisionType collisionType, std::shared_ptr<CollisionDetector> collisionDetector);
		float getWidth();
		float getHeight();
		std::array<Vector2, 4> getBoundNodes();
		void HandleOnAfterOwnerInstantiated() override;
		ColliderType getColliderType() override;
	private:
		float m_Width;
		float m_Height;

		void initializeDebugRender();
		std::shared_ptr<MeshData> createDebugMesh();
	};
}

