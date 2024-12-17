#include "GameManager.h"

namespace BreakoutGame
{
    void GameManager::Initialize()
    {
        m_ScorePoint = 0;
        m_PlayerLives = 3;
        m_CurrentGameState = GameState::MainMenu;

        std::function<void()> onStartButtonHandler = std::bind(&GameManager::onStartButtonClick, this);
        std::function<void()> onQuitButtonHandler = std::bind(&GameManager::onQuitButtonClick, this);
        std::function<void()> onHelpButtonHandler = std::bind(&GameManager::onHelpButtonClick, this);
        m_StateControllerMap[GameState::MainMenu] = std::make_shared<MainMenuController>(onStartButtonHandler, onHelpButtonHandler, onQuitButtonHandler);
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

    std::shared_ptr<InputController> GameManager::GetCurrentInputController()
    {
        return m_StateControllerMap[m_CurrentGameState];
    }

    void GameManager::onStartButtonClick()
    {
        printf("\n Start");
    }

    void GameManager::onQuitButtonClick()
    {
        printf("\n Quit");
    }
    void GameManager::onHelpButtonClick()
    {
        printf("\n help");
    }
}