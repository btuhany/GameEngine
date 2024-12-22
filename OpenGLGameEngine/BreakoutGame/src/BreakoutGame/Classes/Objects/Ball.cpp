#include "Ball.h"

namespace BreakoutGame
{
	void Ball::Initialize(std::shared_ptr<Shader> shader, std::function<void(std::shared_ptr<GameEntity>)> handler)
	{
		IsOnPaddle = true;
		m_OnBallColliderEnterHandler = handler;
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
		m_Speed = SPEED;
		m_Entity->transform->SetPosition(glm::vec3(5.0f, 0.0f, 1.1f));
	}

	void Ball::Tick(float deltaTime)
	{
		m_DeltaTime = deltaTime;

		if (!m_Entity->getActive())
			return;

		if (IsOnPaddle)
			return;

		handleMovement();
		handleRotationAnimation(deltaTime);
	}

	std::shared_ptr<SpriteEntity> Ball::getEntity()
	{
		return m_Entity;
	}
	void Ball::Reset(Vector3 pos)
	{
		SetDefaultSpeed();
		IsOnPaddle = true;
		m_Entity->transform->ResetRotation();
		m_Entity->transform->SetPosition(pos);
	}
	void Ball::StopMovement()
	{
		m_Entity->transform->ResetRotation();
		m_MovementVector = glm::vec3(0.0f);
	}
	void Ball::StartMovement(Vector3 movementVector)
	{
		m_MovementVector = glm::normalize(VectorUtility::Vector3ToGlmVec3(movementVector));
		m_CanMove = true;
	}
	void Ball::ApplyImpulseToMovement(Vector3 impulseVector, float impulseMultiplier)
	{
		auto glmVec = VectorUtility::Vector3ToGlmVec3(impulseVector);
		float length = glm::length(glmVec);
		if (length > 0) //normalize bug
		{
			auto impulseVec = glm::normalize(glmVec);
			m_MovementVector += impulseVec * impulseMultiplier;
			m_MovementVector.z = 0.0f;
			m_MovementVector = glm::normalize(m_MovementVector);
		}
	}
	void Ball::SetPosition(glm::vec3 position)
	{
		m_Entity->transform->SetPosition(position);
	}

	void Ball::MoveLeft()
	{
		if (!m_CanMove)
			return;

		auto leftVector = glm::vec3(-10.0f, 0.0f, 0.0f);
		m_Entity->transform->Translate(leftVector * m_DeltaTime);
	}
	void Ball::MoveRight()
	{
		if (!m_CanMove)
			return;

		auto rightVector = glm::vec3(10.0f, 0.0f, 0.0f);
		m_Entity->transform->Translate(rightVector* m_DeltaTime);
	}
	void Ball::MoveUp()
	{
		if (!m_CanMove)
			return;

		auto upVector = glm::vec3(0.0f, 10.0f, 0.0f);
		m_Entity->transform->Translate(upVector* m_DeltaTime);
	}
	void Ball::MoveDown()
	{
		if (!m_CanMove)
			return;

		auto downVector = glm::vec3(0.0f, -10.0f, 0.0f);
		m_Entity->transform->Translate(downVector* m_DeltaTime);
	}
	void Ball::SetSpeed(float value)
	{
		m_Speed = value;
	}
	float Ball::getSpeed()
	{
		return m_Speed;
	}
	void Ball::SetDefaultSpeed()
	{
		m_Speed = SPEED;
	}
	void Ball::DisableMovement()
	{
		m_CanMove = false;
	}
	void Ball::EnableMovement()
	{
		m_CanMove = true;
	}
	void Ball::onCollisionEnter(std::shared_ptr<CollisionData> collisionData)
	{
		if (!m_Entity->getActive())
		{
			return;
		}

		/*std::cout << "Ball HandleOnCollision Enter pos, x: " << collisionData->collidedNodePos.x << " y: " << collisionData->collidedNodePos.y << std::endl;*/

		auto otherCollider = collisionData->otherCollider;
		auto colliderEntityPtr = otherCollider->getEntity();
		if (colliderEntityPtr.expired())
		{
			return;
		}
		auto colliderEntity = colliderEntityPtr.lock();
		int tagIndex = colliderEntity->getTag();
		
		if (tagIndex == (int)Tag::Perk)
		{
			return;
		}

		if (IsClone && tagIndex == (int)Tag::DeathBoundary) //BAD PRACTICE 
		{
			m_Entity->setActive(false);
		}

		if (otherCollider->getColliderType() == ColliderType::BoxCollider2D)
		{
			if (IS_LOGS_ACTIVE)
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
				if (IS_LOGS_ACTIVE)
					LOG_ERROR("Normal Vector calculated as zero!");
			}
			else if (Vector2::IsAligned(normalVec, m_MovementVector, 0.2f))
			{
				if (IS_LOGS_ACTIVE)
					LOG_ERROR_STREAM("Normal vector: " << normalVec.toString() << " and movement vector : " << m_MovementVector.x << m_MovementVector.y << "is aligned");
				return;
			}


			if (IS_LOGS_ACTIVE)
			{
				LOG_INFO_STREAM("Ball Movement vector, x: " << m_MovementVector.x << " y: " << m_MovementVector.y);
				LOG_INFO_STREAM("Ball Normal vector, x: " << normalVec.x << " y: " << normalVec.y);
			}

			//FINE TUNING FOR PADDLE
			if (colliderEntity->getTag() == (int)Tag::Paddle && avarageCollidedNodePos.y > colliderEntity->transform->getPosition().y)
			{
				if (normalVec.y == 0 && std::abs(normalVec.x) == 1)
				{
					normalVec.y = 1.0f;
					if (normalVec.x > 0)
					{
						normalVec.x = 0.8f;
					}
					else
					{
						normalVec.x = -0.8f;
					}
					
					normalVec = normalVec.normalize();
					LOG_INFO("Ball collide paddle normal calculated with fine tuning");
				}
			}
			auto newMovementVector = glm::reflect(m_MovementVector, glm::vec3(normalVec.x, normalVec.y, 0.0f));

			if (IS_LOGS_ACTIVE)
				LOG_INFO_STREAM("Ball After Reflect New Movement vector, x: " << newMovementVector.x << " y: " << newMovementVector.y);

			m_MovementVector = glm::normalize(newMovementVector);

			if (m_OnBallColliderEnterHandler != nullptr)
				m_OnBallColliderEnterHandler(colliderEntity);
				
		}
	}
	void Ball::onCollisionExit(std::shared_ptr<CollisionData> collisionData)
	{

	}
	void Ball::handleMovement()
	{
		if (!m_CanMove)
			return;

		m_Entity->transform->Translate(m_MovementVector * m_DeltaTime * m_Speed);
	}
	void Ball::handleRotationAnimation(float deltaTime)
	{
		if (!m_CanMove)
			return;

		if (m_MovementVector.x < 0)
		{
			m_Entity->transform->Rotate(ROTATE_ANIM_SPEED, glm::vec3(0.0f, 0.0f, 1.0f));
		}
		else
		{
			m_Entity->transform->Rotate(ROTATE_ANIM_SPEED * -1.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		}
	}
}
