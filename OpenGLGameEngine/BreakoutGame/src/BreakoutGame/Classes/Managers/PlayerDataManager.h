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
		int GetPlayerLevel();
		void ProcessBallHitBrickData(BallHitBrickData hitData);
	private:
		int m_ScorePoint;
		int m_Lives;
		int m_Level;
	};
}

