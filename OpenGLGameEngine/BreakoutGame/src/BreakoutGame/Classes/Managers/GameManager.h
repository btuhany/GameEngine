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
		int GetPlayerLive();
		void ProcessBallHitBrickData(BallHitBrickData hitData);
	private:
		//PLAYER DATA
		int m_ScorePoint;
		int m_PlayerLives;
	};
}


