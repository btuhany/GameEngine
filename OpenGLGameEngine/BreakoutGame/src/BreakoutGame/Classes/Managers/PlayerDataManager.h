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
		void IncreasePlayerLevel(int value);
		void IncreasePlayerLives(int value);
		void DecreasePlayerLives(int value);
		void ProcessBallHitBrickData(BallHitBrickData hitData);
		static const int INITAL_LIVES = 3;
		static const int INITIAL_SCORE_POINT = 0;
		static const int INITAL_LEVEL = 0;
	private:
		int m_ScorePoint;
		int m_Lives;
		int m_Level;
	};
}

