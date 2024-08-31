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

        Entity() = default;
        template<typename T>
        void AddComponent(std::shared_ptr<T> component);

        template<typename T>
        std::shared_ptr<T> GetComponent();

    protected:
        std::unordered_map<std::type_index, std::shared_ptr<Component>> m_ComponentMap;
    };

}

