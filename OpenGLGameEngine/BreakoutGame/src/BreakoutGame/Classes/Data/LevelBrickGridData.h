#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <GameEngine.h>
#include "LevelDataCommon.h"
#include "BrickTypeEnum.h"
#include "BrickGridData.h"
namespace BreakoutGame
{
	static class LevelBrickGridData
	{
	public:
		static void Initialize();
		static void ConvertLevelBrickDataToBrickTypeMatrix();
		static BrickGridData GetBrickGridData(int index);
		static int GetLevelCount();
	private:
		static BrickType getBrickType(std::string str);
		static BrickGridData brickGridDataArr[LEVEL_COUNT];
		static bool m_IsInitialized;
		static std::unordered_map<std::string, BrickType> m_StringToBrickTypeMap;
		static const std::array<std::string[ROW_SIZE][COLUMN_SIZE], LEVEL_COUNT> m_LevelBrickDataList;
	};
}