#include "GameManager.h"

namespace BreakoutGame
{
    void GameManager::Initialize(std::shared_ptr<UIManager> uiManager)
    {
        m_ScorePoint = 0;
        m_PlayerLives = 3;
        m_CurrentGameState = GameState::MainMenu;

        std::function<void()> onStartButtonHandler = std::bind(&GameManager::onMainMenuStartButtonClick, this);
        std::function<void()> onQuitButtonHandler = std::bind(&GameManager::onMainMenuQuitButtonClick, this);
        m_StateControllerMap[GameState::MainMenu] = std::make_shared<MainMenuController>(uiManager, onStartButtonHandler, onQuitButtonHandler);
    }
    void GameManager::Start()
    {
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
    std::shared_ptr<InputController> GameManager::GetController()
    {
        return m_StateControllerMap[m_CurrentGameState];
    }
    void GameManager::ActivateStateController()
    {
        GetController()->HandleOnActivated();
    }
    void GameManager::onMainMenuStartButtonClick()
    {
    }
    void GameManager::onMainMenuQuitButtonClick()
    {
    }
}