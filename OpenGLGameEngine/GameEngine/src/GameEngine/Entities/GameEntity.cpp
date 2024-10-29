#include "GameEntity.h"

namespace GameEngine
{
    GameEntity::GameEntity()
    {
        m_IsActive = false;
		transform = std::make_shared<Transform>();
		AddComponent<Transform>(transform);
        setName("NoNameGameEntity");
    }
    bool GameEntity::IsActive()
    {
        return m_IsActive;
    }
    void GameEntity::setActive(bool isActive)
    {
        m_IsActive = isActive;
        /*for (auto it = m_ComponentMap.begin(); it != m_ComponentMap.end(); ++it) {
            it->second->setEnabled(isActive);
        }*/
    }
    bool GameEntity::getActive()
    {
        return m_IsActive;
    }
    bool GameEntity::IsRegistered()
    {
        return m_IsInstantiated;
    }
    void GameEntity::HandleOnAfterInstantiated()
    {
        m_IsInstantiated = true;
        for (auto it = m_ComponentMap.begin(); it != m_ComponentMap.end(); ++it) {
            it->second->AssignToEntity(shared_from_this());
            it->second->setEnabled(true);
            it->second->HandleOnAfterOwnerInstantiated();
        }
    }
    void GameEntity::HandleOnPreDestroyed()
    {
        for (auto it = m_ComponentMap.begin(); it != m_ComponentMap.end(); ++it) {
            auto compEventData = std::make_shared<ComponentEvent>();
            compEventData->comp = it->second;
            compEventData->compAction = ComponentAction::OwnerPreDestroyed;
            EventManager::GetInstance().Publish(compEventData);
        }
    }
    void GameEntity::setName(std::string name)
    {
        m_Name = name;
    }
    std::string GameEntity::getName()
    {
        return m_Name;
    }
}