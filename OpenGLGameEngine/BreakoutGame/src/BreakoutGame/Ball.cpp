#include "Ball.h"

namespace BreakoutGame
{
	void Ball::Initialize()
	{
		static const char* vShaderLocation = "src/BreakoutGame/Shaders/shader.vert";
		static const char* fShaderLocation = "src/BreakoutGame/Shaders/shader.frag";
		std::shared_ptr<Shader> mainShader = std::make_shared<Shader>();
		mainShader->CreateFromFiles(vShaderLocation, fShaderLocation);

		std::shared_ptr<Texture> texture = std::make_shared<Texture>("src/BreakoutGame/Textures/58-Breakout-Tiles.PNG");
		texture->LoadTextureWithAlpha();

		std::shared_ptr<SpriteRenderData> renderData = std::make_shared<SpriteRenderData>(texture, nullptr, mainShader);

		m_Entity = std::make_shared<SpriteEntity>(renderData);

		std::string name = "Ball";
		m_Entity->setName(name);

		auto detector = std::make_shared<CollisionDetector>();
		auto boxCollider = std::make_shared<BoxCollider2DComponent>(1.8f, 1.8f, CollisionType::Dynamic, detector);
		detector->AddCollisionCallback(CollisionState::Enter,
			[this](std::shared_ptr<ColliderComponent> collider) {
				onCollisionEnter(collider);
			});

		m_Entity->AddComponent(boxCollider);
	}

	void Ball::Start()
	{
		m_Speed = 5.0f;
		m_Entity->transform->SetPosition(glm::vec3(5.0f, 0.0f, 0.0f));
		m_MovementVector = glm::vec3(m_Speed, 0.0f, 0.0f);
	}

	void Ball::Tick(float deltaTime)
	{
		m_Entity->transform->Translate(m_MovementVector * deltaTime);
	}

	std::shared_ptr<SpriteEntity> Ball::getEntity()
	{
		return m_Entity;
	}
	void Ball::onCollisionEnter(std::shared_ptr<ColliderComponent> otherCollider)
	{
		m_Speed *= (-1.0f);
		m_MovementVector = glm::vec3(m_Speed, 0.0f, 0.0f);
	}
}
