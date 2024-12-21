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
#include "../StartModeSettings.h"
namespace GameEngine
{
	enum class BoxColliderPosType
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
		void HandleOnOwnerSetActive(bool isActive) override;
		void HandleOnPreOwnerDestroyed() override;
		ColliderType getColliderType() override;
		Vector2 ProcessGetNormalVector(Vector2 collisionPos);
		void SetEnableStaticSingleNormalVector(bool enabled, Vector2 normalVector = Vector2::zero);
		void SetWidthAndHeight(float width, float height);
		void UpdateDebugMesh();
	private:
		float m_Width;
		float m_Height;

		void initializeDebugRender();
		std::shared_ptr<MeshData> createDebugMesh();
		Vector2 getNodePosition(BoxColliderPosType position);
		const float CORNER_ALIGN_CHECK_THRESHOLD = 0.99999f;

		bool m_UseStaticSingleNormalVector = false;
		Vector2 m_StaticSingleNormalVector = Vector2::zero;
#if _DEBUG
	private:
		std::shared_ptr<DebugRenderData> m_DebugMeshRenderData;
#endif
	};
}

