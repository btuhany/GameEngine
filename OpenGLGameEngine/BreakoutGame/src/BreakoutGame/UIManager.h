#pragma once
#include <GameEngine.h>
namespace BreakoutGame
{
	class UIManager
	{
	public:
		void Initialize();

	private:
		UITextRendererComponent m_ScoreCounterTextComponent;
	};
}

