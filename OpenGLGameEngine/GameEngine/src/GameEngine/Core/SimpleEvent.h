#pragma once
#include <functional>
#include <vector>

namespace GameEngine
{
	template<typename... Args>
	//temp event system for inputs
	class SimpleEvent
	{
	public:
		void AddHandler(std::function<void(Args...)> handler)
		{
			m_Handlers.push_back(handler);
		}
		void Trigger(Args... args)
		{
			for (size_t i = 0; i < m_Handlers.size(); i++)
			{
				m_Handlers[i](std::forward<Args>(args)...);
			}
		}
	private:
		std::vector<std::function<void()>> m_Handlers;
	};
}

