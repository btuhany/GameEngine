#include "GameManager.h"
namespace BreakoutGame
{
    void GameManager::Initialize()
    {
        m_ScorePoint = 0;
    }
    void GameManager::Start()
    {
    }
    void GameManager::IncreaseScorePoint(int value)
    {
        m_ScorePoint += value;
    }
    int GameManager::GetScorePoint()
    {
        return m_ScorePoint;
    }
}