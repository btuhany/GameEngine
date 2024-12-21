#pragma once
#include "BreakoutObject.h"
#include "IMovable.h"
namespace BreakoutGame
{
	class Paddle : public BreakoutObject, public IMovable
	{
	public:
		void Initialize(std::shared_ptr<Shader> shader);
		void Start() override;
		void Tick(float deltaTime) override;
		std::shared_ptr<SpriteEntity> getEntity() override;
		void MoveLeft() override;
		void MoveRight() override;
		void MoveUp() override;
		void MoveDown() override;
		void ResetPos();
		void DisableMovement();
		void EnableMovement();
		glm::vec3 GetBallHolderPosition();
		void ScaleUpWidth(float value);
		void ScaleDownWidth(float value);
		void SetToDefault();
		void IncreaseSpeed(float value);
		float getFakeSpeed();
		bool getCanMove();
	private:
		Vector2 m_DefaultScale;
		std::shared_ptr<BoxCollider2DComponent> m_Collider;
		bool m_CanMove;
		float m_Speed;
		float m_DeltaTime;
		glm::vec3 m_BallHolderOffset;
		const glm::vec3 START_POS = glm::vec3(0.0f, -20.0f, 0.0f);
		const float DEFAULT_SPEED = 35.0f;

		float m_FakeSpeed = 0.0f; //for transfering momentum into the ball
		float m_FakeFrictionMultiplier = 3.0f;
	};
}

