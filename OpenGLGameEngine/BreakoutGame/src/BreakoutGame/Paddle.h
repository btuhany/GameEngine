#pragma once
#include <GameEngine.h>

namespace BreakoutGame
{
	class Paddle
	{
	public:
		void Initialize(std::shared_ptr<Shader> shader);
		void Start();
		void Tick(float deltaTime);
		void MoveLeft();
		void MoveRight();
		std::shared_ptr<SpriteEntity> getEntity();
	private:
		std::shared_ptr<SpriteEntity> m_Entity;
		float m_Speed;
		float m_DeltaTime;
	};
}

