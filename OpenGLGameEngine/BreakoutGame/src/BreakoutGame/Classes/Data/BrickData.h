#pragma once
namespace BreakoutGame
{
	struct BrickData
	{
		//HIT DATA
		int hitCountToBreak = 0;
		int scorePointOnHit = 0;
		int scorePointOnBreak = 0;
		BrickType brickType;
		//PERK DATA
		float perkDropRateOnHit = 0.0f;
		float perkDropRateOnBreak = 0.0f;
	};
}