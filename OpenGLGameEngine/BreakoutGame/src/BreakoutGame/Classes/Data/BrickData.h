#pragma once
namespace BreakoutGame
{
	struct BrickData
	{
		int hitCountToBreak = 0;
		int scorePointOnHit = 0;
		int scorePointOnBreak = 0;
		bool isAbleToDropPerk = false;
		BrickType brickType;
	};
}