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
	private:
		void onCollisionEnter(std::shared_ptr<CollisionData> collisionData);
		glm::vec3 m_MovementVector = glm::vec3(0.0f);
		float m_DeltaTime;
	};
}

