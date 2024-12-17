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
		m_Entity->AddComponent(boxCollider);
	}
	void Paddle::Start()
	{
		m_Speed = 35.0f;
		m_BallHolderOffset = glm::vec3(0.0f, 2.0f, 0.1f);
		m_Entity->transform->SetPosition(START_POS);
	}
	void Paddle::Tick(float deltaTime)
	{
		m_DeltaTime = deltaTime;
	}
	void Paddle::MoveLeft()
	{
		auto leftVector = glm::vec3(-1.0f, 0.0f, 0.0f);
		m_Entity->transform->Translate(leftVector * m_Speed * m_DeltaTime);
	}
	void Paddle::MoveRight()
	{
		auto rightVector = glm::vec3(1.0f, 0.0f, 0.0f);
		m_Entity->transform->Translate(rightVector * m_Speed * m_DeltaTime);
	}
	void Paddle::MoveUp()
	{
		auto upVector = glm::vec3(0.0f, 1.0f, 0.0f);
		m_Entity->transform->Translate(upVector * m_Speed * m_DeltaTime);
	}
	void Paddle::MoveDown()
	{
		auto downVector = glm::vec3(0.0f, -1.0f, 0.0f);
		m_Entity->transform->Translate(downVector * m_Speed * m_DeltaTime);
	}
	void Paddle::Reset()
	{
		m_Entity->transform->SetPosition(START_POS);
	}
	glm::vec3 Paddle::GetBallHolderPosition()
	{
		return m_Entity->transform->getPosition() + m_BallHolderOffset;
	}
	std::shared_ptr<SpriteEntity> Paddle::getEntity()
	{
		return m_Entity;
	}
}
