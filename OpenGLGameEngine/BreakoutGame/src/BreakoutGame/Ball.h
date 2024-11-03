#pragma once
#include <GameEngine.h>
namespace BreakoutGame
{
	class Ball
	{
	public:
		void Initialize();
		void Tick(float deltaTime);
		std::shared_ptr<SpriteEntity> getEntity();
	private:
		std::shared_ptr<SpriteEntity> m_Entity;
	};
}

