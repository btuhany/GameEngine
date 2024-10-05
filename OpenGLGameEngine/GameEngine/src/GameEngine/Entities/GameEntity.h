#pragma once
#include <unordered_map>
#include <typeindex>
#include <memory>
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
        void SetActive(bool isActive);
        bool IsRegistered();
        void RegisterToScene();
        std::shared_ptr<Transform> transform;

        template<typename T>
        void AddComponent(std::shared_ptr<T> component);

        template<typename T>
        std::shared_ptr<T> GetComponent();

    protected:
        std::unordered_map<std::type_index, std::shared_ptr<Component>> m_ComponentMap;

	private:
		bool m_isActive;
        bool m_isRegistered; //is assigned to scene
    };

    template<typename T>
    void GameEntity::AddComponent(std::shared_ptr<T> component)
    {
        static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");
        
        std::shared_ptr<Component> baseComponent = std::static_pointer_cast<Component>(component);

        m_ComponentMap[typeid(T)] = component;


		auto event = std::make_shared<ComponentEvent>();
		event->Comp = baseComponent;
        event->CompAction = ComponentAction::Added;
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
}



