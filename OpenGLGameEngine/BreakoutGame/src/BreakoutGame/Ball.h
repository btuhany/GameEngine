#pragma once
#include <GameEngine.h>
namespace BreakoutGame
{
	class Ball
	{
	public:
		void Initialize(std::shared_ptr<Shader> shader);
		void Start();
		void Tick(float deltaTime);
		std::shared_ptr<SpriteEntity> getEntity();
	private:
		std::shared_ptr<SpriteEntity> m_Entity;
		void onCollisionEnter(std::shared_ptr<ColliderComponent> otherCollider);
		glm::vec3 m_MovementVector = glm::vec3(0.0f);
		float m_Speed = 0.01f;
	};
}

