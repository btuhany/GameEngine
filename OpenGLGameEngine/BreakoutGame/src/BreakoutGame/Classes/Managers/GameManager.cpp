#include "GameManager.h"

namespace BreakoutGame
{
    void GameManager::Initialize()
    {
        m_ScorePoint = 0;
        m_PlayerLives = 3;
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

}