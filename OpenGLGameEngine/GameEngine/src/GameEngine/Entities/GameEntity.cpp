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
    void GameEntity::setActive(bool isActive)
    {
        m_isActive = isActive;
        for (auto it = m_ComponentMap.begin(); it != m_ComponentMap.end(); ++it) {
            it->second->setEnabled(isActive);
        }
    }
    bool GameEntity::IsRegistered()
    {
        return m_isRegistered;
    }
    void GameEntity::RegisterToScene()
    {
        m_isRegistered = true;
        for (auto it = m_ComponentMap.begin(); it != m_ComponentMap.end(); ++it) {
            it->second->AssignToEntity(shared_from_this());
        }
    }
}