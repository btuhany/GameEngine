#pragma once
#include "BreakoutObject.h"
namespace BreakoutGame
{
	class Ball : public BreakoutObject
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
		std::shared_ptr<SpriteEntity> m_Entity;
		void onCollisionStay(std::shared_ptr<CollisionData> collisionData);
		glm::vec3 m_MovementVector = glm::vec3(0.0f);
		float m_Speed = 0.01f;
		float m_DeltaTime;
	};
}

