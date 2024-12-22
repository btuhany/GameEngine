#pragma once
#include <GameEngine.h>
#include "BrickTypeEnum.h"
namespace BreakoutGame
{
	struct BallHitBrickData
	{
		int gainedScorePoint = 0;
		bool isBroken = false;
		Vector3 brickPos;
		BrickType brickType;
	};
}