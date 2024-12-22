#pragma once
#include <GameEngine.h>
#include "BrickTypeEnum.h"
#include "BrickData.h"
namespace BreakoutGame
{
	class BrickProperties
	{
	public:
		BrickData data;
		std::vector<std::shared_ptr<SpriteRenderData>> spriteRenderDataListOrderedHitCountAscending;
	};
}

