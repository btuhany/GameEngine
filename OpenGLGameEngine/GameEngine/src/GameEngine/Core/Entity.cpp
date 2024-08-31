#include "Entity.h"

namespace GameEngine
{
    template<typename T>
    void Entity::AddComponent(std::shared_ptr<T> component)
    {
        m_ComponentMap[typeid(T)] = component;
    }

    template<typename T>
    std::shared_ptr<T> Entity::GetComponent()
    {
        auto it = m_ComponentMap.find(typeid(T));
        if (it != m_ComponentMap.end()) {
            return std::static_pointer_cast<T>(it->second);
        }
        return nullptr;
    }

}