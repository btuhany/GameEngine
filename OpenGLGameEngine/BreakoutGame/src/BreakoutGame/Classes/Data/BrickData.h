#pragma once
#include <GameEngine.h>
#include <memory>
namespace BreakoutGame
{
	class BrickData
	{
	public:
		int hitCountToBreak = 0;
		bool isAbleToDropPerk = false;
		bool isAbleToDropScorePoint = false;
		bool isAbleToDropHealthPoint = false;
		std::vector<Texture> texturesHitCountAscendingOrder;
	};
}

