#include "PlayerDataManager.h"
namespace BreakoutGame
{
    PlayerDataManager::PlayerDataManager()
    {
        ResetData();
    }
    void PlayerDataManager::ResetData()
    {
        m_ScorePoint = 0;
        m_PlayerLives = 3;
    }
    int PlayerDataManager::GetScorePoint()
    {
        return m_ScorePoint;
    }
    int PlayerDataManager::GetPlayerLive()
    {
        return m_PlayerLives;
    }
    void PlayerDataManager::ProcessBallHitBrickData(BallHitBrickData hitData)
    {
        m_ScorePoint += hitData.gainedScorePoint;
    }
}