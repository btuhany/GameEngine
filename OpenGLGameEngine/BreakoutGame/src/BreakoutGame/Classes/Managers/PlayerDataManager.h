#pragma once
#include "../Data/BallHitBrickData.h"
namespace BreakoutGame
{
	class PlayerDataManager
	{
	public:
		PlayerDataManager();
		void ResetData();
		int GetScorePoint();
		int GetPlayerLive();
		void ProcessBallHitBrickData(BallHitBrickData hitData);
	private:
		int m_ScorePoint;
		int m_PlayerLives;
	};
}

