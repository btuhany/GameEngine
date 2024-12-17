#pragma once
#include <string>
#include <vector>
#include "BrickTypeEnum.h"
#include <unordered_map>
#include <GameEngine.h>
namespace BreakoutGame
{
	static const int LEVEL_COUNT = 5;
	static const int COLUMN_SIZE = 11;
	static const int ROW_SIZE = 6;

	static class LevelBrickGridData
	{
	public:
		struct BrickGridDataHolder
		{
		public:
			BrickType BrickGrid[ROW_SIZE][COLUMN_SIZE];
		};

		static void Initialize();
		static void ConvertLevelBrickDataToBrickTypeMatrix();
		static BrickType GetBrickType(std::string str);
	private:
		static BrickGridDataHolder brickGridDataArr[LEVEL_COUNT];
		static bool m_IsInitialized;
		static std::unordered_map<std::string, BrickType> m_StringToBrickTypeMap;
		static const std::array<std::string[ROW_SIZE][COLUMN_SIZE], LEVEL_COUNT> m_LevelBrickDataList;
	};
}