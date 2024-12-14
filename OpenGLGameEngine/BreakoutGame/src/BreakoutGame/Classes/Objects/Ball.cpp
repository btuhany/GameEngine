#include "Ball.h"

namespace BreakoutGame
{
	void Ball::Initialize(std::shared_ptr<Shader> shader)
	{
		m_OnBallColliderEnterHandler = nullptr;

		std::shared_ptr<Texture> texture = std::make_shared<Texture>("src/BreakoutGame/Textures/58-Breakout-Tiles.PNG");
		texture->LoadTextureWithAlpha();

		std::shared_ptr<SpriteRenderData> renderData = std::make_shared<SpriteRenderData>(texture, nullptr, shader);

		m_Entity = std::make_shared<SpriteEntity>(renderData);

		std::string name = "Ball";
		m_Entity->setName(name);
		m_Entity->setTag((int)Tag::Ball);
		auto detector = std::make_shared<CollisionDetector>();
		auto boxCollider = std::make_shared<BoxCollider2DComponent>(1.8f, 1.8f, CollisionType::Dynamic, detector);
		detector->AddCollisionCallback(CollisionState::Enter,
			[this](std::shared_ptr<CollisionData> collider) {
				onCollisionEnter(collider);
			});
		detector->AddCollisionCallback(CollisionState::Exit,
			[this](std::shared_ptr<CollisionData> collider) {
				onCollisionExit(collider);
			});

		m_Entity->AddComponent(boxCollider);
	}

	void Ball::Start()
	{
		m_Speed = 30.0f;
		m_Entity->transform->SetPosition(glm::vec3(5.0f, 0.0f, 1.1f));
	}

	void Ball::Tick(float deltaTime)
	{
		if (!m_Entity->getActive())
			return;

		m_DeltaTime = deltaTime;
		handleMovement();
	}

	std::shared_ptr<SpriteEntity> Ball::getEntity()
	{
		return m_Entity;
	}
	void Ball::StopMovement()
	{
		m_MovementVector = glm::vec3(0.0f);
		m_IsMoving = false;
	}
	void Ball::StartMovement(Vector3 movementVector)
	{
		m_MovementVector = glm::normalize(glm::vec3(movementVector.x, movementVector.y, movementVector.z));
		m_IsMoving = true;
	}
	void Ball::SetPosition(glm::vec3 position)
	{
		m_Entity->transform->SetPosition(position);
	}
	void Ball::SetOnBallColliderEnterHandler(std::function<void(std::shared_ptr<GameEntity>)> handler)
	{
		m_OnBallColliderEnterHandler = handler;
	}
	void Ball::MoveLeft()
	{
		auto leftVector = glm::vec3(-10.0f, 0.0f, 0.0f);
		m_Entity->transform->Translate(leftVector * m_DeltaTime);
	}
	void Ball::MoveRight()
	{
		auto rightVector = glm::vec3(10.0f, 0.0f, 0.0f);
		m_Entity->transform->Translate(rightVector* m_DeltaTime);
	}
	void Ball::MoveUp()
	{
		auto upVector = glm::vec3(0.0f, 10.0f, 0.0f);
		m_Entity->transform->Translate(upVector* m_DeltaTime);
	}
	void Ball::MoveDown()
	{
		auto downVector = glm::vec3(0.0f, -10.0f, 0.0f);
		m_Entity->transform->Translate(downVector* m_DeltaTime);
	}
	void Ball::SetSpeed(float value)
	{
		m_Speed = value;
	}
	void Ball::onCollisionEnter(std::shared_ptr<CollisionData> collisionData)
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
			LOG_INFO("------BALL COLLISION------");
			auto boxCollider = std::static_pointer_cast<BoxCollider2DComponent>(otherCollider);
			auto avarageCollidedNodePos = Vector2::zero;
			for (size_t i = 0; i < collisionData->collidedNodePosList.size(); i++)
			{
				auto pos = Vector2(collisionData->collidedNodePosList[i]);
				avarageCollidedNodePos = avarageCollidedNodePos + (pos / collisionData->collidedNodePosList.size());
			}

			//std::cout << "avarageCollidedNodePos: " << avarageCollidedNodePos.toString() << std::endl;
			auto normalVec = boxCollider->ProcessGetNormalVector(avarageCollidedNodePos);
			if (normalVec == Vector2::zero)
			{
				LOG_ERROR("Normal Vector calculated as zero!");
			}
			else if (Vector2::IsAligned(normalVec, m_MovementVector, 0.2f))
			{
				LOG_ERROR("Normal vector and movement vector is aligned");
				return;
			}



			LOG_INFO_STREAM("Ball Movement vector, x: " << m_MovementVector.x << " y: " << m_MovementVector.y);
			LOG_INFO_STREAM("Ball Normal vector, x: " << normalVec.x << " y: " << normalVec.y);
			auto newMovementVector = glm::reflect(m_MovementVector, glm::vec3(normalVec.x, normalVec.y, 0.0f));
			LOG_INFO_STREAM("Ball After Reflect New Movement vector, x: " << newMovementVector.x << " y: " << newMovementVector.y);

			m_MovementVector = newMovementVector;

			if (m_OnBallColliderEnterHandler != nullptr)
				m_OnBallColliderEnterHandler(colliderEntity);
				
		}
	}
	void Ball::onCollisionExit(std::shared_ptr<CollisionData> collisionData)
	{

	}
	void Ball::handleMovement()
	{
		if (!m_IsMoving)
			return;

		m_Entity->transform->Translate(m_MovementVector * m_DeltaTime * m_Speed);
	}
}
