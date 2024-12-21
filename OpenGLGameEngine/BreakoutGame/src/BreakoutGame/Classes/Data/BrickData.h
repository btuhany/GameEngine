#pragma once
#include <GameEngine.h>
#include <memory>
#include "BrickTypeEnum.h"
namespace BreakoutGame
{
	class BrickData
	{
	public:
		int hitCountToBreak = 0;
		int scorePointOnHit = 0;
		int scorePointOnBreak = 0;
		bool isAbleToDropPerk = false;
		std::vector<std::shared_ptr<SpriteRenderData>> spriteRenderDataListOrderedHitCountAscending;
		BrickType brickType;
	};
}

