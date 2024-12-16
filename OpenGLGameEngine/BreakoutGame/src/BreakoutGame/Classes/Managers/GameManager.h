#pragma once
#include "../Data/BallHitBrickData.h"
namespace BreakoutGame
{
	class GameManager
	{
	public:
		void Initialize();
		void Start();
		int GetScorePoint();
		void ProcessBallHitBrickData(BallHitBrickData hitData);
		bool isGameStarted;
	private:
		//PLAYER DATA
		int m_ScorePoint;
		int m_BrokenBrickCount;
	};
}


