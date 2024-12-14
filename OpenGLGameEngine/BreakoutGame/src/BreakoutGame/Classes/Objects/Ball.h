#pragma once
#include "BreakoutObject.h"
#include "IMovable.h"
namespace BreakoutGame
{
	class Ball : public BreakoutObject, public IMovable
	{
	public:
		void Initialize(std::shared_ptr<Shader> shader) override;
		void Start() override;
		void Tick(float deltaTime) override;
		std::shared_ptr<SpriteEntity> getEntity() override;

		void MoveLeft() override;
		void MoveRight() override;
		void MoveUp() override;
		void MoveDown() override;

		void StopMovement();
		void StartMovement(Vector3 movementVector);
		void SetPosition(glm::vec3 position);
		void SetOnBallColliderEnterHandler(std::function<void(std::shared_ptr<GameEntity>)> handler);
		//debug purposes
		void SetSpeed(float value);

	private:
		std::function<void(std::shared_ptr<GameEntity>)> m_OnBallColliderEnterHandler;
		void onCollisionEnter(std::shared_ptr<CollisionData> collisionData);
		void onCollisionExit(std::shared_ptr<CollisionData> collisionData);
		void handleMovement();
		bool m_IsMoving = false;
		glm::vec3 m_MovementVector = glm::vec3(0.0f);
		float m_DeltaTime;
	};
}

