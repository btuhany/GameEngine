#pragma once
#include <GameEngine.h>
#include "Ball.h"
namespace BreakoutGame
{
	class CloneBallController
	{
	public:
		void Initialize(std::shared_ptr<Shader> shader, std::function<void(std::shared_ptr<GameEntity>)> handler);
		void Tick(float deltaTime);
		void ActivateClones(Vector3 pos);
		std::vector<std::shared_ptr<GameEntity>> getEntitiyList();
	private:
		std::vector<std::shared_ptr<Ball>> m_CloneBallList;
		const int CLONE_BALL_COUNT = 3;
	};
}
