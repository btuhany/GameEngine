#include "PlayerDataManager.h"
namespace BreakoutGame
{
    const int INITAL_LIVES = 3;
    const int INITIAL_SCORE_POINT = 0;
    const int INITAL_LEVEL = 0;
    PlayerDataManager::PlayerDataManager()
    {
        ResetData();
    }
    void PlayerDataManager::ResetData()
    {
        //TODO Initial data
        m_Level = INITAL_LEVEL;
        m_ScorePoint = INITIAL_SCORE_POINT;
        m_Lives = INITAL_LIVES;
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
    void PlayerDataManager::IncreasePlayerLevel(int value)
    {
        m_Level += value;
    }
    void PlayerDataManager::IncreasePlayerLives(int value)
    {
        m_Lives += value;
        if (m_Lives > INITAL_LIVES)
        {
            m_Lives = INITAL_LIVES;
        }
    }
    void PlayerDataManager::DecreasePlayerLives(int value)
    {
        m_Lives -= value;
        if (m_Lives <= 0)
        {
            m_Lives = 0;
        }
    }
    void PlayerDataManager::ProcessBallHitBrickData(BallHitBrickData hitData)
    {
        m_ScorePoint += hitData.gainedScorePoint;
    }
}