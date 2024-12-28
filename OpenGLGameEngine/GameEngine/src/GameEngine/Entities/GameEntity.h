#pragma once
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <string>
#include "../Components/Component.h"
#include "../Core.h"
#include "../Event/ComponentEvent.h"
#include "../Event/EventManager.h"
#include "../Components/Transform.h"

namespace GameEngine
{
    class ENGINE_API GameEntity : public std::enable_shared_from_this<GameEntity>
    {
    public:
        GameEntity();
        bool IsActive();
        void setActive(bool isActive);
        bool getActive();
        bool IsRegistered();
        void HandleOnAfterInstantiated();
        void HandleOnPreDestroyed();
        void setName(std::string name);
        void setTag(int tag);
        int getTag();
        std::string getName();
        std::shared_ptr<Transform> transform;

        template<typename T>
        void AddComponent(std::shared_ptr<T> component);

        template<typename T>
        std::shared_ptr<T> GetComponent();

        template<typename T>
        std::shared_ptr<T> GetComponentOfBaseType();

    protected:
        std::unordered_map<std::type_index, std::shared_ptr<Component>> m_ComponentMap;

	private:
        int m_Tag = 0;
		bool m_IsActive = false;
        bool m_IsInstantiated = false; //is assigned to scene
        std::string m_Name;
    };

    //TODO: unnecessary T Template?
    template<typename T>
    void GameEntity::AddComponent(std::shared_ptr<T> component)
    {
        static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");
        
        std::shared_ptr<Component> baseComponent = std::static_pointer_cast<Component>(component);

        m_ComponentMap[typeid(T)] = component;


		auto event = std::make_shared<ComponentEvent>();
		event->comp = baseComponent;
        event->compAction = ComponentAction::Added;
		EventManager::GetInstance().Publish(event);
    }

    template<typename T>
    std::shared_ptr<T> GameEntity::GetComponent()
    {
        auto it = m_ComponentMap.find(typeid(T));
        if (it != m_ComponentMap.end()) {
            return std::static_pointer_cast<T>(it->second);
        }
        return nullptr;
    }

    template<typename T>
    std::shared_ptr<T> GameEntity::GetComponentOfBaseType()
    {
        for (const auto& entry : m_ComponentMap) {
            auto casted = std::dynamic_pointer_cast<T>(entry.second);
            if (casted) {
                return casted;
            }
        }
        return nullptr;
    }
}



