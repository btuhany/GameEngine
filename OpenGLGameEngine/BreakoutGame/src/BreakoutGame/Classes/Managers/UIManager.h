#pragma once
#include <GameEngine.h>
namespace BreakoutGame
{
	class UIManager
	{
	public:
		void Initialize();
		std::vector<std::shared_ptr<GameEntity>> getEntityList();
	private:
		std::shared_ptr<UITextRendererComponent> m_ScoreCounterTextComponent;
		std::vector<std::shared_ptr<GameEntity>> m_GameEntityList;
	};
}

