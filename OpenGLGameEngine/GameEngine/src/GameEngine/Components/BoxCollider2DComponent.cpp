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

		auto ownerPos = m_OwnerEntity.lock()->transform->getPosition();

		//top-left
		boundArr[(int)BoxColliderPosTypes::TopLeft] = Vector2(
			ownerPos.x - (m_Width / 2.0f),
			ownerPos.y + (m_Height / 2.0f));
		//top-right
		boundArr[(int)BoxColliderPosTypes::TopRight] = Vector2(
			ownerPos.x + (m_Width / 2.0f),
			ownerPos.y + (m_Height / 2.0f));
		//bottom-right
		boundArr[(int)BoxColliderPosTypes::BottomRight] = Vector2(
			ownerPos.x + (m_Width / 2.0f),
			ownerPos.y - (m_Height / 2.0f));
		//bottom-left
		boundArr[(int)BoxColliderPosTypes::BottomLeft] = Vector2(
			ownerPos.x - (m_Width / 2.0f), 
			ownerPos.y - (m_Height / 2.0f));

		return boundArr;
	}

	ColliderType BoxCollider2DComponent::getColliderType()
	{
		return ColliderType::BoxCollider2D;
	}

	void BoxCollider2DComponent::HandleOnAfterOwnerInstantiated()
	{
		initializeDebugRender();
	}

	void BoxCollider2DComponent::initializeDebugRender()
	{
#if _DEBUG
		if (true)
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
#endif
	}
	std::shared_ptr<MeshData> BoxCollider2DComponent::createDebugMesh()
	{
		GLfloat vertices[] =
		{
			//x      y     z		 u     y			normals
			-1.0f, -1.0f, 0.0f, 	0.0f, 1.0f,		0.0f, 0.0f, 1.0f,
			1.0f, -1.0f, 0.0f,	1.0f, 1.0f,		0.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 1.0f,
			-1.0f, 1.0f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 1.0f
		};

		unsigned int indices[] = {
			0,1,2,
			2,3,0
		};

		std::shared_ptr<MeshData> cubeMesh = std::make_shared<MeshData>();
		cubeMesh->CreateMesh(vertices, indices, 32, 6);
		return cubeMesh;
	}
}
