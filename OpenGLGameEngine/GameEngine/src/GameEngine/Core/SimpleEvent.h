#pragma once
#include <functional>
#include <vector>
namespace GameEngine
{
	//temp event system for inputs
	class SimpleEvent
	{
	public:
		void AddHandler(std::function<void()> handler);
		void Trigger();
	private:
		std::vector<std::function<void()>> m_Handlers;
	};
}

