#pragma once
#include <typeindex>
#include <string>
#include <algorithm>
#include <iostream>
#include "../Core.h"
#include "Event.h"
#include "../Debugging/Log.h"

namespace GameEngine
{

	class ENGINE_API EventManager {
	public:
		static EventManager& GetInstance() {
			static EventManager instance;
			return instance;
		}

		template <typename EventType>
		void Subscribe(std::function<void(std::shared_ptr<EventType>)> callback, int priority = 0) {
			const std::type_index eventType = EventType().getType();
			m_Listeners[eventType].emplace_back(
				[callback](std::shared_ptr<IEvent> e) {
					callback(std::static_pointer_cast<EventType>(e));
				},
				priority
			);

			std::sort(m_Listeners[eventType].begin(), m_Listeners[eventType].end(),
				[](const Listener& a, const Listener& b) {
					return a.Priority > b.Priority;
				});
		}


		template <typename EventType>
		void Unsubscribe(std::function<void(std::shared_ptr<EventType>)> callback) {
			const std::type_index eventType = EventType().getType();
			auto& eventListeners = m_Listeners[eventType];

			//eventListeners.erase(std::remove_if(eventListeners.begin(), eventListeners.end(),
			//	[&callback](const Listener& listener) {
			//		return listener.Callback.target<void(std::shared_ptr<EventType>)>() == callback.target<void(std::shared_ptr<EventType>)>();
			//	}),
			//	eventListeners.end());

			auto it = std::find_if(eventListeners.begin(), eventListeners.end(),
				[&callback](const Listener& listener) {
					return listener.Callback.target<void(std::shared_ptr<EventType>)>() == callback.target<void(std::shared_ptr<EventType>)>();
				});

			if (it == eventListeners.end()) {
				LOG_CORE_WARN("No listener found");
				return;
			}


			eventListeners.erase(it);
		}

		void Publish(std::shared_ptr<IEvent> event) {
			const std::type_index eventType = event->getType();
			if (m_Listeners.find(eventType) != m_Listeners.end()) 
			{
				for (auto& listener : m_Listeners[eventType]) 
				{
					listener.Callback(event);
				}
			}
			else
			{
				LOG_CORE_WARN("There is no listener of the event");
			}
		}


		EventManager(const EventManager&) = delete;
		EventManager& operator=(const EventManager&) = delete;
	private:
		std::unordered_map<std::type_index, std::vector<Listener>> m_Listeners;

		EventManager() = default;
	};
}