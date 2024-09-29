#include "GameEntity.h"

namespace GameEngine
{
    GameEntity::GameEntity()
    {
        m_isActive = false;
		transform = std::make_shared<Transform>();
		AddComponent<Transform>(transform);
    }
    bool GameEntity::IsActive()
    {
        return m_isActive;
    }
    void GameEntity::SetActive(bool isActive)
    {
        m_isActive = isActive;
    }
    bool GameEntity::IsRegistered()
    {
        return m_isRegistered;
    }
    void GameEntity::RegisterToScene()
    {
        m_isRegistered = true;
    }
}