#include "LevelBrickGridData.h"

namespace BreakoutGame
{
    bool LevelBrickGridData::m_IsInitialized = false;
    std::unordered_map<std::string, BrickType> LevelBrickGridData::m_StringToBrickTypeMap;
    BrickGridData LevelBrickGridData::brickGridDataArr[LEVEL_COUNT];

    const std::array<std::string[ROW_SIZE][COLUMN_SIZE], LEVEL_COUNT> LevelBrickGridData::m_LevelBrickDataList =
    {{
        {
            { ".", ".", "e", "e", ".", ".", ".", "e", "e", ".", "." },
            { ".", ".", "h", "h", ".", ".", ".", "h", "h", ".", "." },
            { "m", ".", ".", ".", ".", ".", ".", ".", ".", ".", "m" },
            { "m", "m", ".", ".", ".", ".", ".", ".", ".", "m", "m" },
            { ".", "m", "e", "e", "e", "e", "e", "e", "e", "m", "." },
            { ".", ".", "m", ".", ".", ".", ".", ".", "m", ".", "." }
        },
        {
            { ".", ".", "m", "m", "m", ".", "m", "m", "m", ".", "." },
            { ".", ".", "m", "h", "m", ".", "m", "h", "m", ".", "." },
            { ".", "m", "e", "m", "m", "e", "m", "m", "e", "m", "." },
            { "m", "e", ".", ".", ".", ".", ".", ".", ".", "e", "m" },
            { ".", "m", "e", "m", "m", "e", "m", "m", "e", "m", "." },
            { ".", ".", "m", ".", ".", ".", ".", ".", "m", ".", "." }
        },
        {
            { "e", "e", "e", "h", "e", "e", "e", "h", "e", "e", "e" },
            { ".", ".", "m", ".", "h", "h", "h", ".", "m", ".", "." },
            { "h", "h", "h", "h", "h", ".", "h", "h", "h", "h", "h" },
            { ".", ".", "m", ".", "h", "h", "h", ".", "m", ".", "." },
            { ".", ".", "m", "h", ".", ".", ".", "h", "m", ".", "." },
            { "e", "e", "h", "e", "e", "e", "e", "e", "h", "e", "e" }
        }
    }};

    void LevelBrickGridData::Initialize()
    {
        m_StringToBrickTypeMap = {
            {".", BrickType::None},
            {"e", BrickType::Easy},
            {"m", BrickType::Medium},
            {"h", BrickType::Hard},
        };


        ConvertLevelBrickDataToBrickTypeMatrix();

        m_IsInitialized = true;
    }

    void LevelBrickGridData::ConvertLevelBrickDataToBrickTypeMatrix()
    {
        for (int level = 0; level < LEVEL_COUNT; ++level)
        {
            auto& brickStrGrid = m_LevelBrickDataList[level];
            for (int row = 0; row < ROW_SIZE; ++row) {
                for (int col = 0; col < COLUMN_SIZE; ++col) {
                    auto& str = brickStrGrid[row][col];

                    if (m_StringToBrickTypeMap.find(str) != m_StringToBrickTypeMap.end())
                    {
                        brickGridDataArr[level].grid[row][col] = getBrickType(str);
                    }
                    else
                    {
                        LOG_ERROR("LEVELBRICKGRIDDATA | ConvertLevelBrickDataToBrickTypeMatrix | string to brick type map key not found: " + str);
                    }
                }
            }
        }
    }

    BrickGridData LevelBrickGridData::GetBrickGridData(int index)
    {
        if (!m_IsInitialized)
        {
            LOG_ERROR("LevelBrickGridData | GetBrickGridData | Class not initialized");
        }
        if (index >= LEVEL_COUNT)
        {
            LOG_ERROR("LevelBrickGridData | GetBrickGridData | Index is greater than level count");
        }

        return brickGridDataArr[index];
    }

    int LevelBrickGridData::GetLevelCount()
    {
        return LEVEL_COUNT;
    }

    BrickType LevelBrickGridData::getBrickType(std::string str)
    {
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
    }
}