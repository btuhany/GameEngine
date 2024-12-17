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
		void Reset();
		glm::vec3 GetBallHolderPosition();
	private:
		float m_Speed;
		float m_DeltaTime;

		glm::vec3 m_BallHolderOffset;
	};
}

