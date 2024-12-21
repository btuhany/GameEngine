#pragma once
#include <GameEngine.h>
#include "Ball.h"
namespace BreakoutGame
{
	class CloneBallController
	{
	public:
		void Initialize(std::shared_ptr<Ball> mainBall);
		void Tick(float deltaTime);
		void ActivateClones();

	private:

		std::vector<std::shared_ptr<Ball>> m_CloneBallList;
		const int CLONE_BALL_COUNT = 2;
	};
}
