#pragma once
#include <GameEngine.h>

#include "../Data/GameStateEnum.h"
#include "../StateControllers/MainMenuState.h"
#include "../StateControllers/InGameState.h"
namespace BreakoutGame
{
	class StateManager
	{
	public:
		void Initialize(std::shared_ptr<MainMenuState> mainMenuStateController, std::shared_ptr<InGameState> inGameStateController, std::function<void()> onGameQuitCallback);
		void Start();
		void Tick(float deltaTime);
		GameState GetGameState();
		std::shared_ptr<StateBase> GetController();
	private:
		GameState m_CurrentGameState;
		std::function<void()> m_OnGameQuitCallback;
		void changeGameState(GameState newState);
		void onMainMenuStartButtonClick();
		void onMainMenuQuitButtonClick();
		void onAllLevelsCompleted();
		std::unordered_map<GameState, std::shared_ptr<StateBase>> m_StateControllerMap;



	};
}


