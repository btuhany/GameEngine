#pragma once
#include <GameEngine.h>
#include "IEntityProvider.h"
namespace BreakoutGame
{
	class UIManager : public IEntityProvider
	{
	public:
		void Initialize(float viewPortWidth, float viewPortHeight);
		void SetScorePoint(int scorePoint);
		std::vector<std::shared_ptr<GameEntity>> getEntityList();
		void Start();
	private:
		float m_ViewPortWidth, m_ViewPortHeight;
		std::shared_ptr<UITextRendererComponent> m_ScoreCounterTextComponent;
		std::vector<std::shared_ptr<GameEntity>> m_GameEntityList;
	};
}

