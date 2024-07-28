#include "SimpleEvent.h"

void GameEngine::SimpleEvent::AddHandler(std::function<void()> handler)
{
	m_Handlers.push_back(handler);
}

void GameEngine::SimpleEvent::Trigger()
{
	for (size_t i = 0; i < m_Handlers.size(); i++)
	{
		m_Handlers[i]();
	}
}
