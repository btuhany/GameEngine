#pragma once
#include <vector>

namespace GameEngine
{
	//temp event system for inputs
	class SimpleEvent
	{
	public:
		void AddHandler(std::function<void()> handler)
		{
			m_Handlers.push_back(handler);
		}

		void Trigger()
		{
			for (size_t i = 0; i < m_Handlers.size(); i++)
			{
				m_Handlers[i]();
			}
		}
	private:
		std::vector<std::function<void()>> m_Handlers;
	};
}

