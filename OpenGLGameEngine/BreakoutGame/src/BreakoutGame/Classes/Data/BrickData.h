#pragma once
#include <GameEngine.h>
#include <memory>
namespace BreakoutGame
{
	enum class BrickType
	{
		Easy,
		Medium,
		Hard
	};

	class BrickData
	{
	public:
		BrickType type;
		int hitCountToBreak = 0;
		int scorePointOnHit = 0;
		int scorePointOnBreak = 0;
		bool isAbleToDropPerk = false;
		bool isAbleToDropExtraScorePoint = false;
		bool isAbleToDropHealthPoint = false;
		std::vector<std::shared_ptr<SpriteRenderData>> spriteRenderDataListOrderedHitCountAscending;
	};
}

