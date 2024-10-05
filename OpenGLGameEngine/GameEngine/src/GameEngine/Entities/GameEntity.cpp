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
        /*for (auto it = m_ComponentMap.begin(); it != m_ComponentMap.end(); ++it) {
            it->second->setEnabled(isActive);
        }*/
    }
    bool GameEntity::getActive()
    {
        return m_isActive;
    }
    bool GameEntity::IsRegistered()
    {
        return m_isInstantiated;
    }
    void GameEntity::HandleOnAfterInstantiated()
    {
        m_isInstantiated = true;
        for (auto it = m_ComponentMap.begin(); it != m_ComponentMap.end(); ++it) {
            it->second->HandleOnAfterOwnerInstantiated();
            it->second->AssignToEntity(shared_from_this());
            it->second->setEnabled(true);
        }
    }
    void GameEntity::HandleOnPreDestroyed()
    {
        for (auto it = m_ComponentMap.begin(); it != m_ComponentMap.end(); ++it) {
            auto compEvent = std::make_shared<ComponentEvent>();
            compEvent->Comp = it->second;
            compEvent->CompAction = ComponentAction::OwnerPreDestroyed;
            EventManager::GetInstance().Publish(compEvent);
        }
    }
    void GameEntity::setName(std::string name)
    {
        m_name = name;
    }
    std::string GameEntity::getName()
    {
        return m_name;
    }
}