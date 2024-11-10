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

	/// <summary>
	/// Calculates where a point is from 4 regions of the box. 
	/// </summary>
	/// <param name="collisionPos"></param>
	/// <returns></returns>
	Vector2 BoxCollider2DComponent::ProcessGetNormalVector(Vector2 collisionPos)
	{
		auto entity = getEntity();
		if (entity.expired())
		{
			return;
		}
		auto colliderEntityPos = Vector2(entity.lock()->transform->getPosition());
		auto collisionVec = (collisionPos - colliderEntityPos).normalize();

		auto collidedNodes = getBoundNodes();
		auto topRightVec = (collidedNodes[(int)BoxColliderPosType::TopRight] - colliderEntityPos).normalize();
		auto bottomRightVec = (collidedNodes[(int)BoxColliderPosType::BottomRight] - colliderEntityPos).normalize();

		auto yPosInTopRightVec = collisionVec.x * (topRightVec.y / topRightVec.x);
		auto yPosInBottomRightVec = collisionVec.x * (bottomRightVec.y / bottomRightVec.x);

		std::cout << "Ball yPosInBottomRightVec, x: " << yPosInBottomRightVec << std::endl;
		std::cout << "Ball yPosInTopRightVec, x: " << yPosInTopRightVec << std::endl;

		Vector2 normalVector = Vector2::zero;
		if (collisionVec.x > 0)
		{
			if (collisionVec.y > yPosInTopRightVec)
			{
				//UP
				normalVector = Vector2::up;
			}
			else if (collisionVec.y <= yPosInTopRightVec && collisionVec.y >= yPosInBottomRightVec)
			{
				//RIGHT
				normalVector = Vector2::right;
			}
			else if (collisionVec.y < yPosInBottomRightVec)
			{
				//DOWN
				normalVector = Vector2::down;
			}
		}
		else if (collisionVec.x < 0)
		{
			if (collisionVec.y > yPosInBottomRightVec)
			{
				//UP
				normalVector = Vector2::up;
			}
			else if (collisionVec.y >= yPosInTopRightVec && collisionVec.y <= yPosInBottomRightVec)
			{
				//LEFT
				normalVector = Vector2::left;
			}
			else if (collisionVec.y < yPosInTopRightVec)
			{
				//DOWN
				normalVector = Vector2::down;
			}
		}
		else if (collisionVec.x == 0)
		{
			if (collisionVec.y > 0)
			{
				//UP
				normalVector = Vector2::up;
			}
			else if (collisionVec.y < 0)
			{
				//BOTTOM
				normalVector = Vector2::down;
			}
			else if (collisionVec.y == 0)
			{
				//MID?
				normalVector = Vector2::zero;
			}
		}

		std::cout << "Ball HandleOnCollision Normal vector, x: " << normalVector.x << " y: " << normalVector.y << std::endl;

		return normalVector;

	}

	void BoxCollider2DComponent::HandleOnAfterOwnerInstantiated()
	{
#if _DEBUG
		initializeDebugRender();
#endif
	}

	void BoxCollider2DComponent::HandleOnOwnerSetActive(bool isActive)
	{
#if _DEBUG
		if (SETTINGS_COLLIDER_DEBUG_MODE)
		{
			if (m_OwnerEntity.expired())
			{
				LOG_CORE_ERROR("BoxCollider2DComponent | HandleOnOwnerSetActive owner is null");
				return;
			}

			auto it = Renderer::DebugMeshRenderDataTransformMap.find(m_OwnerEntity.lock());
			if (isActive)
			{
				if (it == Renderer::DebugMeshRenderDataTransformMap.end())
				{
					Renderer::DebugMeshRenderDataTransformMap[m_OwnerEntity.lock()] = m_DebugMeshRenderData;
				}
			}
			else
			{
				if (it != Renderer::DebugMeshRenderDataTransformMap.end())
				{
					Renderer::DebugMeshRenderDataTransformMap.erase(it);
				}
			}
		}
#endif
	}

	void BoxCollider2DComponent::HandleOnPreOwnerDestroyed()
	{
#if _DEBUG
		if (SETTINGS_COLLIDER_DEBUG_MODE)
		{
			if (m_OwnerEntity.expired())
			{
				LOG_CORE_ERROR("BoxCollider2DComponent | HandleOnOwnerSetActive owner is null");
				return;
			}

			auto it = Renderer::DebugMeshRenderDataTransformMap.find(m_OwnerEntity.lock());
			if (it != Renderer::DebugMeshRenderDataTransformMap.end())
			{
				Renderer::DebugMeshRenderDataTransformMap.erase(it);
			}
		}
#endif
	}

	void BoxCollider2DComponent::initializeDebugRender()
	{
		if (SETTINGS_COLLIDER_DEBUG_MODE)
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

			m_DebugMeshRenderData = std::make_shared<DebugRenderData>(createDebugMesh(), colliderDebugShader);
			auto it = Renderer::DebugMeshRenderDataTransformMap.find(m_OwnerEntity.lock());
			if (it == Renderer::DebugMeshRenderDataTransformMap.end())
				Renderer::DebugMeshRenderDataTransformMap[m_OwnerEntity.lock()] = m_DebugMeshRenderData;
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
