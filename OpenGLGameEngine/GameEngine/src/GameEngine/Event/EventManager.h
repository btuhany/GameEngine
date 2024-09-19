#pragma once
#include <typeindex>
#include <string>
#include <algorithm>
#include <iostream>
#include "../Core.h"
#include "Event.h"

namespace GameEngine
{

	class ENGINE_API EventManager {
	public:
		template <typename EventType>
		void Subscribe(std::function<void(std::shared_ptr<EventType>)> callback, int priority = 0) {
			const std::string eventName = EventType().GetName();
			m_Listeners[eventName].emplace_back(
				[callback](std::shared_ptr<Event> e) {
					callback(std::static_pointer_cast<EventType>(e));
				},
				priority
			);

			std::sort(m_Listeners[eventName].begin(), m_Listeners[eventName].end(),
				[](const Listener& a, const Listener& b) {
					return a.Priority > b.Priority;
				});
		}


		template <typename EventType>
		void Unsubscribe(std::function<void(std::shared_ptr<EventType>)> callback) {
			const std::string eventName = EventType().GetName();
			auto& eventListeners = m_Listeners[eventName];

			eventListeners.erase(std::remove_if(eventListeners.begin(), eventListeners.end(),
				[&callback](const Listener& listener) {
					return listener.Callback.target<void(std::shared_ptr<EventType>)>() == callback.target<void(std::shared_ptr<EventType>)>();
				}),
				eventListeners.end());
		}

		void Publish(std::shared_ptr<Event> event) {
			const std::string eventName = event->GetName();
			if (m_Listeners.find(eventName) != m_Listeners.end()) {
				for (auto& listener : m_Listeners[eventName]) {
					listener.Callback(event);
				}
			}
		}

	private:
		std::unordered_map<std::string, std::vector<Listener>> m_Listeners;
	};
}