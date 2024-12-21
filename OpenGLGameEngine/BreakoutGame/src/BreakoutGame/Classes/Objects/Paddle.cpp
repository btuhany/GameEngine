#include "Paddle.h"

namespace BreakoutGame
{
	void Paddle::Initialize(std::shared_ptr<Shader> shader)
	{
		std::shared_ptr<Texture> texture = std::make_shared<Texture>("src/BreakoutGame/Textures/49-Breakout-Tiles.PNG");
		texture->LoadTextureWithAlpha();

		std::shared_ptr<SpriteRenderData> renderData = std::make_shared<SpriteRenderData>(texture, nullptr, shader);

		m_Entity = std::make_shared<SpriteEntity>(renderData);

		std::string name = "Paddle";
		m_Entity->setName(name);
		m_Entity->setTag((int)Tag::Paddle);
		auto boxCollider = std::make_shared<BoxCollider2DComponent>(7.5f, 2.0f, CollisionType::Static);
		m_Collider = boxCollider;
		m_Entity->AddComponent(boxCollider);
	}
	void Paddle::SetToDefault()
	{
		m_Entity->transform->SetScale(glm::vec3(m_DefaultScale.x, m_DefaultScale.y, m_Entity->transform->getScale().z));
		m_Collider->SetWidthAndHeight(7.5f, 2.0f);
	}
	void Paddle::IncreaseSpeed(float value)
	{
		m_Speed += value;
	}
	float Paddle::getFakeSpeed()
	{
		return m_FakeSpeed;
	}
	bool Paddle::getCanMove()
	{
		return m_CanMove;
	}
	void Paddle::Start()
	{
		auto scale = m_Entity->transform->getScale();
		m_DefaultScale = Vector2(scale.x, scale.y);
		m_Speed = DEFAULT_SPEED;
		m_BallHolderOffset = glm::vec3(0.0f, 2.0f, 0.1f);
		m_Entity->transform->SetPosition(START_POS);
	}
	void Paddle::Tick(float deltaTime)
	{
		m_DeltaTime = deltaTime;

		if (m_FakeSpeed > 0)
		{
			m_FakeSpeed = std::max((m_FakeSpeed - (m_FakeFrictionMultiplier * deltaTime)), 0.0f);
		}
		else if (m_FakeSpeed < 0)
		{
			m_FakeSpeed = std::min((m_FakeSpeed + (m_FakeFrictionMultiplier * deltaTime)), 0.0f);
		}
		LOG_INFO("FakeSpeed: " + std::to_string(m_FakeSpeed));
	}
	void Paddle::MoveLeft()
	{
		if (!m_CanMove)
			return;

		m_FakeSpeed = -1.0f;
		auto leftVector = glm::vec3(-1.0f, 0.0f, 0.0f);
		m_Entity->transform->Translate(leftVector * m_Speed * m_DeltaTime);
	}
	void Paddle::MoveRight()
	{
		if (!m_CanMove)
			return;

		m_FakeSpeed = 1.0f;
		auto rightVector = glm::vec3(1.0f, 0.0f, 0.0f);
		m_Entity->transform->Translate(rightVector * m_Speed * m_DeltaTime);
	}
	void Paddle::MoveUp()
	{
		if (!m_CanMove)
			return;

		auto upVector = glm::vec3(0.0f, 1.0f, 0.0f);
		m_Entity->transform->Translate(upVector * m_Speed * m_DeltaTime);
	}
	void Paddle::MoveDown()
	{
		if (!m_CanMove)
			return;

		auto downVector = glm::vec3(0.0f, -1.0f, 0.0f);
		m_Entity->transform->Translate(downVector * m_Speed * m_DeltaTime);
	}
	void Paddle::ResetPos()
	{
		m_Entity->transform->SetPosition(START_POS);
	}
	void Paddle::DisableMovement()
	{
		m_CanMove = false;
	}
	void Paddle::EnableMovement()
	{
		m_CanMove = true;
	}
	glm::vec3 Paddle::GetBallHolderPosition()
	{
		return m_Entity->transform->getPosition() + m_BallHolderOffset;
	}
	void Paddle::ScaleUpWidth(float value)
	{
		float scaleIncrease = value;
		auto scale = m_Entity->transform->getScale();
		glm::vec3 newScale = glm::vec3(scale.x + scaleIncrease, scale.y, scale.z);
		m_Entity->transform->SetScale(newScale);

		auto colliderWidth = m_Collider->getWidth();
		auto colliderHeight = m_Collider->getHeight();
		scaleIncrease *= 2;
		auto colliderNewWidth = colliderWidth + scaleIncrease;
		m_Collider->SetWidthAndHeight(colliderNewWidth, colliderHeight);
		m_Collider->UpdateDebugMesh();
	}
	void Paddle::ScaleDownWidth(float value)
	{
		float scaleDecrease = value;
		auto scale = m_Entity->transform->getScale();
		glm::vec3 newScale = glm::vec3(scale.x - scaleDecrease, scale.y, scale.z);
		m_Entity->transform->SetScale(newScale);

		auto colliderWidth = m_Collider->getWidth();
		auto colliderHeight = m_Collider->getHeight();

		scaleDecrease *= 2;
		auto colliderNewWidth = colliderWidth - scaleDecrease;
		m_Collider->SetWidthAndHeight(colliderNewWidth, colliderHeight);
		m_Collider->UpdateDebugMesh();
	}
	std::shared_ptr<SpriteEntity> Paddle::getEntity()
	{
		return m_Entity;
	}
}
