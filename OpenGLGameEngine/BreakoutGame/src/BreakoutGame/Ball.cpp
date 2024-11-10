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
		detector->AddCollisionCallback(CollisionState::Stay,
			[this](std::shared_ptr<CollisionData> collider) {
				onCollisionStay(collider);
			});

		m_Entity->AddComponent(boxCollider);
	}

	void Ball::Start()
	{
		m_Speed = 2.0f;
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
	void Ball::MoveUp()
	{
		auto upVector = glm::vec3(0.0f, 1.0f, 0.0f);
		m_Entity->transform->Translate(upVector * m_Speed * m_DeltaTime);
	}
	void Ball::MoveDown()
	{
		auto downVector = glm::vec3(0.0f, -1.0f, 0.0f);
		m_Entity->transform->Translate(downVector * m_Speed * m_DeltaTime);
	}
	void Ball::onCollisionStay(std::shared_ptr<CollisionData> collisionData)
	{
		if (!m_Entity->getActive())
			return;

		/*std::cout << "Ball HandleOnCollision Enter pos, x: " << collisionData->collidedNodePos.x << " y: " << collisionData->collidedNodePos.y << std::endl;*/

		auto otherCollider = collisionData->otherCollider;
		auto colliderEntityPtr = otherCollider->getEntity();
		if (colliderEntityPtr.expired())
		{
			return;
		}
		auto colliderEntity = colliderEntityPtr.lock();

		if (otherCollider->getColliderType() == ColliderType::BoxCollider2D)
		{
			auto boxCollider = std::static_pointer_cast<BoxCollider2DComponent>(otherCollider);
			auto normalVec = boxCollider->ProcessGetNormalVector(collisionData->collidedNodePos);
			if (normalVec == Vector2::zero)
			{
				LOG_ERROR("Normal Vector calculated as zero!");
			}
			std::cout << "Ball HandleOnCollision Normal vector, x: " << normalVec.x << " y: " << normalVec.y << std::endl;




		}

		//m_Speed *= (-1.0f);
		//m_MovementVector = glm::vec3(m_Speed, 0.0f, 0.0f);
	}
}
