#pragma once
#include <GameEngine.h>

#include "../Data/GameStateEnum.h"
#include "../StateControllers/MainMenuStateController.h"
#include "../StateControllers/InGameStateController.h"
namespace BreakoutGame
{
	class StateManager
	{
	public:
		void Initialize(std::shared_ptr<MainMenuStateController> mainMenuStateController, std::shared_ptr<InGameStateController> inGameStateController);
		void Start();
		void Tick(float deltaTime);
		GameState GetGameState();
		std::shared_ptr<StateController> GetController();
	private:
		GameState m_CurrentGameState;

		void changeGameState(GameState newState);
		void onMainMenuStartButtonClick();
		void onMainMenuQuitButtonClick();
		std::unordered_map<GameState, std::shared_ptr<StateController>> m_StateControllerMap;



	};
}


