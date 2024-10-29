#include "BoxCollider2DComponent.h"

namespace GameEngine
{
	BoxCollider2DComponent::BoxCollider2DComponent(float width, float height, CollisionType collisionType) : ColliderComponent(collisionType)
	{
		m_Width = width;
		m_Height = height;
	}
	BoxCollider2DComponent::BoxCollider2DComponent(float width, float height, CollisionType collisionType, std::shared_ptr<CollisionDetector> collisionDetector) : ColliderComponent(collisionType, collisionDetector)
	{
		m_Width = width;
		m_Height = height;
	}
	float BoxCollider2DComponent::getWidth()
	{
		return m_Width;
	}

	float BoxCollider2DComponent::getHeight()
	{
		return m_Height;
	}
	std::array<Vector2, 4> BoxCollider2DComponent::getBoundNodes()
	{
		std::array<Vector2, 4> boundArr;
		if (m_OwnerEntity.expired())
		{
			LOG_CORE_ERROR("BoxCollider2DComponent | getBoundNodes, owner expired!");
			return boundArr;
		}

		//top-left
		boundArr[(int)BoxColliderPosType::TopLeft] = getNodePosition(BoxColliderPosType::TopLeft);
		//top-right
		boundArr[(int)BoxColliderPosType::TopRight] = getNodePosition(BoxColliderPosType::TopRight);
		//bottom-right
		boundArr[(int)BoxColliderPosType::BottomRight] = getNodePosition(BoxColliderPosType::BottomRight);
		//bottom-left
		boundArr[(int)BoxColliderPosType::BottomLeft] = getNodePosition(BoxColliderPosType::BottomLeft);

		return boundArr;
	}

	ColliderType BoxCollider2DComponent::getColliderType()
	{
		return ColliderType::BoxCollider2D;
	}

	void BoxCollider2DComponent::HandleOnAfterOwnerInstantiated()
	{
#if _DEBUG
		initializeDebugRender();
#endif
	}

	void BoxCollider2DComponent::initializeDebugRender()
	{
		if (SETTINGS_DEBUG_MODE)
		{
			if (m_OwnerEntity.expired())
			{
				LOG_CORE_ERROR("BoxCollider2DComponent | initializeDebugRender owner is null");
				return;
			}
			static const char* vColliderDebugShaderLocation = "src/BreakoutGame/Shaders/colliderDebugShader.vert";
			static const char* fColliderDebugShaderLocation = "src/BreakoutGame/Shaders/colliderDebugShader.frag";
			std::shared_ptr<Shader> colliderDebugShader = std::make_shared<Shader>();
			colliderDebugShader->CreateFromFiles(vColliderDebugShaderLocation, fColliderDebugShaderLocation);

			auto debugMeshRenderData = std::make_shared<DebugRenderData>(createDebugMesh(), colliderDebugShader);
			Renderer::DebugMeshRenderDataTransformMap[debugMeshRenderData] = m_OwnerEntity.lock()->transform;
		}

	}
	std::shared_ptr<MeshData> BoxCollider2DComponent::createDebugMesh()
	{
		if (m_OwnerEntity.expired())
		{
			LOG_CORE_ERROR("BoxCollider2DComponent | createDebugMesh, owner expired!");
			return nullptr;
		}
		auto ownerPos = m_OwnerEntity.lock()->transform->getPosition();
		auto ownerPosVec2 = Vector2(ownerPos.x, ownerPos.y);
		auto bottomLeftPos = getNodePosition(BoxColliderPosType::BottomLeft) - ownerPosVec2;
		auto bottomRightPos = getNodePosition(BoxColliderPosType::BottomRight) - ownerPosVec2;
		auto topLeftPos = getNodePosition(BoxColliderPosType::TopLeft) - ownerPosVec2;
		auto topRightPos = getNodePosition(BoxColliderPosType::TopRight) - ownerPosVec2;
		GLfloat vertices[] =
		{
			//x      y     z		       u     y	normals
			bottomLeftPos.x, bottomLeftPos.y, 0.0f,	0.0f, 1.0f,	0.0f, 0.0f, 1.0f,  //bottom left
			bottomRightPos.x,bottomRightPos.y, 0.0f,	1.0f, 1.0f,	0.0f, 0.0f, 1.0f,  //bottom right
			topRightPos.x, topRightPos.y, 0.0f,	1.0f, 0.0f,	0.0f, 0.0f, 1.0f,  //top right
			topLeftPos.x,topLeftPos.y, 0.0f,	0.0f, 0.0f,	0.0f, 0.0f, 1.0f   //top left
		};

		unsigned int indices[] = {
			0,1,2,
			2,3,0
		};

		std::shared_ptr<MeshData> cubeMesh = std::make_shared<MeshData>();
		cubeMesh->CreateMesh(vertices, indices, 32, 6);
		return cubeMesh;
	}
	Vector2 BoxCollider2DComponent::getNodePosition(BoxColliderPosType position)
	{
		if (m_OwnerEntity.expired())
		{
			LOG_CORE_ERROR("BoxCollider2DComponent | getNodePosition, owner expired!");
			return Vector2(0.0f, 0.0f);
		}
		auto ownerPos = m_OwnerEntity.lock()->transform->getPosition();

		switch (position)
		{
			case GameEngine::BoxColliderPosType::TopLeft:
				return Vector2(
					ownerPos.x - (m_Width / 2.0f),
					ownerPos.y + (m_Height / 2.0f));
				break;
			case GameEngine::BoxColliderPosType::TopRight:
				return Vector2(
					ownerPos.x + (m_Width / 2.0f),
					ownerPos.y + (m_Height / 2.0f));;
				break;
			case GameEngine::BoxColliderPosType::BottomRight:
				return Vector2(
				ownerPos.x + (m_Width / 2.0f),
				ownerPos.y - (m_Height / 2.0f));
				break;
			case GameEngine::BoxColliderPosType::BottomLeft:
				return Vector2(
					ownerPos.x - (m_Width / 2.0f),
					ownerPos.y - (m_Height / 2.0f));
				break;
			default:
				break;
		}
		return Vector2(0.0f, 0.0f);;
	}
}
