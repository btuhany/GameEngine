#include "CloneBallController.h"
namespace BreakoutGame
{
	void CloneBallController::Initialize(std::shared_ptr<Ball> mainBall)
	{
		for (size_t i = 0; i < CLONE_BALL_COUNT; i++)
		{
			m_CloneBallList.push_back(mainBall->Clone());
		}
	}
	void CloneBallController::Tick(float deltaTime)
	{
		for (size_t i = 0; i < m_CloneBallList.size(); i++)
		{
			m_CloneBallList[i]->Tick(deltaTime);
		}
	}
	void CloneBallController::ActivateClones()
	{
	}
}
