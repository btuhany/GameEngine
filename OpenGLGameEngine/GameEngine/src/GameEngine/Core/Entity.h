#pragma once
#include <unordered_map>
#include <typeindex>
#include <memory>
#include "Component.h"
#include "Core.h"

namespace GameEngine
{
    class ENGINE_API Entity
    {
    public:
        Entity();
        template<typename T>
        void AddComponent(std::shared_ptr<T> component);

        template<typename T>
        std::shared_ptr<T> GetComponent();

    protected:
        std::unordered_map<std::type_index, std::shared_ptr<Component>> m_ComponentMap;
    };

    template<typename T>
    void Entity::AddComponent(std::shared_ptr<T> component)
    {
        static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");

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



