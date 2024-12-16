#include "GameManager.h"

namespace BreakoutGame
{
    void GameManager::Initialize()
    {
        m_ScorePoint = 0;
        m_BrokenBrickCount = 0;
    }
    void GameManager::Start()
    {
    }
    int GameManager::GetScorePoint()
    {
        return m_ScorePoint;
    }
    void GameManager::ProcessBallHitBrickData(BallHitBrickData hitData)
    {
        m_ScorePoint += hitData.gainedScorePoint;
        if (hitData.isBroken)
        {
            m_BrokenBrickCount++;
        }
    }
}