#include "BoxCollider2DComponent.h"

namespace GameEngine
{
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

		auto ownerPos = m_OwnerEntity.lock()->transform->GetPosition();

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
}
