#pragma once
#include <GameEngine.h>
#include "IEntityProvider.h"
namespace BreakoutGame
{
	class UIManager : public IEntityProvider
	{
	public:
		void Initialize();
		std::vector<std::shared_ptr<GameEntity>> getEntityList();
	private:
		std::shared_ptr<UITextRendererComponent> m_ScoreCounterTextComponent;
		std::vector<std::shared_ptr<GameEntity>> m_GameEntityList;
	};
}

