#pragma once
#include "../Data/BallHitBrickData.h"
#include "../Data/GameStateEnum.h"
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
		GameState GetGameState();
	private:
		GameState m_CurrentGameState;
		//PLAYER DATA
		int m_ScorePoint;
		int m_PlayerLives;
	};
}


