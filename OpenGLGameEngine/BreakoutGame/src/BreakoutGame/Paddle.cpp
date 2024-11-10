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

		auto boxCollider = std::make_shared<BoxCollider2DComponent>(1.8f, 1.8f, CollisionType::Static);
		m_Entity->AddComponent(boxCollider);
	}
	void Paddle::Start()
	{
		m_Speed = 4.0f;
		m_Entity->transform->SetPosition(glm::vec3(-0.1f, 5.0f, -0.3f));
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
	}
	void Paddle::MoveDown()
	{
	}
	std::shared_ptr<SpriteEntity> Paddle::getEntity()
	{
		return m_Entity;
	}
}
