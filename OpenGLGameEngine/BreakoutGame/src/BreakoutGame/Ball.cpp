#include "Ball.h"

namespace BreakoutGame
{
	void Ball::Initialize(std::shared_ptr<Shader> shader)
	{
		std::shared_ptr<Texture> texture = std::make_shared<Texture>("src/BreakoutGame/Textures/58-Breakout-Tiles.PNG");
		texture->LoadTextureWithAlpha();

		std::shared_ptr<SpriteRenderData> renderData = std::make_shared<SpriteRenderData>(texture, nullptr, shader);

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
		if (!m_Entity->getActive())
			return;

		m_DeltaTime = deltaTime;
		//m_Entity->transform->Translate(m_MovementVector * deltaTime);
	}

	std::shared_ptr<SpriteEntity> Ball::getEntity()
	{
		return m_Entity;
	}
	void Ball::MoveLeft()
	{
		auto leftVector = glm::vec3(-1.0f, 0.0f, 0.0f);
		m_Entity->transform->Translate(leftVector * m_Speed * m_DeltaTime);
	}
	void Ball::MoveRight()
	{
		auto rightVector = glm::vec3(1.0f, 0.0f, 0.0f);
		m_Entity->transform->Translate(rightVector * m_Speed * m_DeltaTime);
	}
	void Ball::onCollisionEnter(std::shared_ptr<ColliderComponent> otherCollider)
	{
		if (!m_Entity->getActive())
			return;

		otherCollider->getEntity().lock()->setActive(false);
		//if (otherCollider->getColliderType() == ColliderType::BoxCollider2D)
		//{
		//	auto entity = otherCollider->getEntity();
		//	if (entity.expired())
		//	{
		//		return;
		//	}
		//	auto entitySharedPtr = entity.lock();

		//	auto entityPos = entitySharedPtr->transform->getPosition();
		//	auto ballPos = m_Entity->transform->getPosition();

		//	auto relativeVector = glm::normalize(ballPos - entityPos);

		//	if (relativeVector.x > relativeVector.y)
		//	{
		//		
		//	}
		//	else if (relativeVector.x < relativeVector.y)
		//	{

		//	}

		//}

		//m_Speed *= (-1.0f);
		//m_MovementVector = glm::vec3(m_Speed, 0.0f, 0.0f);
	}
}
