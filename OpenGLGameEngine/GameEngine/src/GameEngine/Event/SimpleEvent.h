#pragma once
#include <vector>

namespace GameEngine
{
	//temp event system for inputs
	template<typename... Args>
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
				m_Handlers[i](args...);
			}
		}
	private:
		std::vector<std::function<void(Args...)>> m_Handlers;
	};
}

