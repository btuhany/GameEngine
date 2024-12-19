#include "PlayerDataManager.h"
namespace BreakoutGame
{
    PlayerDataManager::PlayerDataManager()
    {
        ResetData();
    }
    void PlayerDataManager::ResetData()
    {
        //TODO Initial data
        m_Level = 1;
        m_ScorePoint = 0;
        m_Lives = 3;
    }
    int PlayerDataManager::GetScorePoint()
    {
        return m_ScorePoint;
    }
    int PlayerDataManager::GetPlayerLive()
    {
        return m_Lives;
    }
    int PlayerDataManager::GetPlayerLevel()
    {
        return m_Level;
    }
    void PlayerDataManager::ProcessBallHitBrickData(BallHitBrickData hitData)
    {
        m_ScorePoint += hitData.gainedScorePoint;
    }
}