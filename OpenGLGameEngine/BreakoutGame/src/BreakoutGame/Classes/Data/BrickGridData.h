#pragma once
#include "LevelDataCommon.h"
#include "BrickTypeEnum.h"
namespace BreakoutGame
{
	struct BrickGridData
	{
	public:
		BrickType grid[ROW_SIZE][COLUMN_SIZE];
	};
}