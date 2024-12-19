#include "StateManager.h"

namespace BreakoutGame
{
    std::string ToString(GameState state)
    {
        switch (state)
        {
        case GameState::None:
            return "None";
        case GameState::MainMenu:
            return "MainMenu";
        case GameState::InGame:
            return "InGame";
        case GameState::Pause:
            return "Pause";
        default:
            return "Unknown";
        }
    }

    void StateManager::Initialize(std::shared_ptr<MainMenuStateController> mainMenuStateController, std::shared_ptr<InGameStateController> inGameStateController)
    {
        m_ScorePoint = 0;
        m_PlayerLives = 3;
        m_CurrentGameState = GameState::MainMenu;

        std::function<void()> onStartButtonHandler = std::bind(&StateManager::onMainMenuStartButtonClick, this);
        std::function<void()> onQuitButtonHandler = std::bind(&StateManager::onMainMenuQuitButtonClick, this);
        mainMenuStateController->SetCallbacks(onStartButtonHandler, onQuitButtonHandler);


        m_StateControllerMap[GameState::MainMenu] = mainMenuStateController;
        m_StateControllerMap[GameState::InGame] = inGameStateController;
    }
    void StateManager::Start()
    {
        for (auto it = m_StateControllerMap.begin(); it != m_StateControllerMap.end(); ++it)
        {
            it->second->Start();
        }
        changeGameState(m_CurrentGameState);
    }
    void StateManager::Tick(float deltaTime)
    {
        if (m_StateControllerMap.find(m_CurrentGameState) != m_StateControllerMap.end())
        {
            m_StateControllerMap[m_CurrentGameState]->Tick(deltaTime);
        }
    }
    int StateManager::GetScorePoint()
    {
        return m_ScorePoint;
    }
    int StateManager::GetPlayerLive()
    {
        return m_PlayerLives;
    }
    void StateManager::ProcessBallHitBrickData(BallHitBrickData hitData)
    {
        m_ScorePoint += hitData.gainedScorePoint;
    }
    GameState StateManager::GetGameState()
    {
        return m_CurrentGameState;
    }
    std::shared_ptr<StateController> StateManager::GetController()
    {
        return m_StateControllerMap[m_CurrentGameState];
    }
    void StateManager::changeGameState(GameState newState)
    {
        if (m_CurrentGameState != GameState::None)
            m_StateControllerMap[m_CurrentGameState]->HandleOnDeactivated();

        m_CurrentGameState = newState;
        if (m_StateControllerMap.find(m_CurrentGameState) != m_StateControllerMap.end())
        {
            m_StateControllerMap[m_CurrentGameState]->HandleOnActivated();
        }
        else
        {
            std::string logStr = "StateManager | changeGameState | state not exist in map: " + ToString(m_CurrentGameState);
            LOG_INFO(logStr);
        }
    }
    void StateManager::onMainMenuStartButtonClick()
    {
        changeGameState(GameState::InGame);
    }
    void StateManager::onMainMenuQuitButtonClick()
    {
    }
}