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

	static class LevelData
	{
	public:
		static void Initialize() {
			m_StringToBrickTypeMap  = {
			   {"x", BrickType::None},
			   {"e", BrickType::Easy},
			   {"m", BrickType::Medium},
			   {"h", BrickType::Hard},
			};

			m_IsInitialized = true;
		};
		static BrickType GetBrickType(std::string str) {
			if (!m_IsInitialized)
			{
				LOG_ERROR("BRICK TYPE ERROR | NOT INITIALIZED");
				return BrickType::None;
			}

			auto it = m_StringToBrickTypeMap.find(str);
			if (it != m_StringToBrickTypeMap.end()) 
			{
				return m_StringToBrickTypeMap[str];
			}
			else
			{
				LOG_ERROR("BRICK TYPE ERROR | STR DOES NOT EXIST");
				return BrickType::None;
			}
		};
		static const std::array<std::string[ROW_SIZE][COLUMN_SIZE], LEVEL_COUNT> m_LevelBrickDataList;
	private:
		static bool m_IsInitialized;
		static std::unordered_map<std::string, BrickType> m_StringToBrickTypeMap;
	};


}