#include "GameManager.h"

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

    void GameManager::Initialize(std::shared_ptr<UIManager> uiManager)
    {
        m_ScorePoint = 0;
        m_PlayerLives = 3;
        m_CurrentGameState = GameState::MainMenu;

        std::function<void()> onStartButtonHandler = std::bind(&GameManager::onMainMenuStartButtonClick, this);
        std::function<void()> onQuitButtonHandler = std::bind(&GameManager::onMainMenuQuitButtonClick, this);
        m_StateControllerMap[GameState::MainMenu] = std::make_shared<MainMenuStateController>(uiManager, onStartButtonHandler, onQuitButtonHandler);
    }
    void GameManager::Start()
    {
        changeGameState(m_CurrentGameState);
    }
    int GameManager::GetScorePoint()
    {
        return m_ScorePoint;
    }
    int GameManager::GetPlayerLive()
    {
        return m_PlayerLives;
    }
    void GameManager::ProcessBallHitBrickData(BallHitBrickData hitData)
    {
        m_ScorePoint += hitData.gainedScorePoint;
    }
    GameState GameManager::GetGameState()
    {
        return m_CurrentGameState;
    }
    std::shared_ptr<StateController> GameManager::GetController()
    {
        return m_StateControllerMap[m_CurrentGameState];
    }
    void GameManager::changeGameState(GameState newState)
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
            std::string logStr = "GameManager | changeGameState | state not exist in map: " + ToString(m_CurrentGameState);
            LOG_INFO(logStr);
        }
    }
    void GameManager::onMainMenuStartButtonClick()
    {
        changeGameState(GameState::InGame);
    }
    void GameManager::onMainMenuQuitButtonClick()
    {
    }
}