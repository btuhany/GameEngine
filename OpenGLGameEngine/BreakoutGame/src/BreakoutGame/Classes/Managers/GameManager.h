#pragma once
#include <unordered_map>
#include <memory>
#include "../Data/BallHitBrickData.h"
#include "../Data/GameStateEnum.h"
#include "../Controllers/InputController.h"
#include "../Controllers/MainMenuController.h"
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


