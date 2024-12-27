#pragma once
#include "BreakoutObject.h"
#include "IMovable.h"
namespace BreakoutGame
{
	class Ball : public BreakoutObject, public IMovable
	{
	public:
		void Initialize(std::shared_ptr<Shader> shader, std::function<void(std::shared_ptr<GameEntity>)> handler);
		void Start() override;
		void Tick(float deltaTime) override;
		std::shared_ptr<SpriteEntity> getEntity() override;

		void MoveLeft() override;
		void MoveRight() override;
		void MoveUp() override;
		void MoveDown() override;

		void Reset(Vector3 pos);
		void StopMovement();
		void StartMovement(Vector3 movementVector);
		void ApplyImpulseToMovement(Vector3 impulseVector, float impulseMultiplier);
		void SetPosition(glm::vec3 position);
		//debug purposes
		void SetSpeed(float value);
		float getSpeed();
		void SetDefaultSpeed();
		void DisableMovement();
		void EnableMovement();
		bool IsOnPaddle = false;
		//FOR CLONE PERK
		bool IsClone = false;  //Bad :(
		int CloneHitCount = 0;
	private:
		bool m_CanMove;
		std::function<void(std::shared_ptr<GameEntity>)> m_OnBallColliderEnterHandler;
		void onCollisionEnter(std::shared_ptr<CollisionData> collisionData);
		void onCollisionExit(std::shared_ptr<CollisionData> collisionData);
		void handleMovement();
		void handleRotationAnimation(float deltaTime);
		glm::vec3 m_MovementVector = glm::vec3(0.0f);
		float m_DeltaTime;
		const float SPEED = 37.0f;
		//FOR DEBUG
		const bool IS_LOGS_ACTIVE = true;
		const float ROTATE_ANIM_SPEED = 2.8f;
	};
}

