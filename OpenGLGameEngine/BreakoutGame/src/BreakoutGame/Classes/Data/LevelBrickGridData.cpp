#include "LevelBrickGridData.h"

namespace BreakoutGame
{
    bool LevelBrickGridData::m_IsInitialized = false;
    std::unordered_map<std::string, BrickType> LevelBrickGridData::m_StringToBrickTypeMap;
    LevelBrickGridData::BrickGridDataHolder LevelBrickGridData::brickGridDataArr[LEVEL_COUNT];

    const std::array<std::string[ROW_SIZE][COLUMN_SIZE], LEVEL_COUNT> LevelBrickGridData::m_LevelBrickDataList =
    {{
        {
            { "e", "x", "x", "x", "x", "x", "x", "x", "x", "x", "x" },
            { "x", "e", "x", "x", "x", "x", "x", "x", "x", "x", "x" },
            { "x", "x", "e", "x", "x", "x", "x", "x", "x", "x", "x" },
            { "x", "x", "x", "e", "x", "x", "x", "x", "x", "x", "x" },
            { "x", "x", "x", "x", "e", "x", "x", "x", "x", "x", "x" },
            { "x", "x", "x", "x", "x", "e", "x", "x", "x", "x", "x" }
        },
        {
            { "m", "x", "x", "x", "x", "x", "x", "x", "x", "x", "m" },
            { "m", "x", "x", "x", "x", "x", "x", "x", "x", "x", "m" },
            { "m", "x", "x", "x", "x", "x", "x", "x", "x", "x", "m" },
            { "m", "x", "x", "x", "x", "x", "x", "x", "x", "x", "m" },
            { "m", "x", "x", "x", "x", "x", "x", "x", "x", "x", "m" },
            { "m", "x", "x", "x", "x", "x", "x", "x", "x", "x", "m" }
        },
        {
            { "m", "x", "x", "x", "x", "x", "x", "x", "m", "x", "x" },
            { "x", "h", "x", "x", "x", "x", "x", "x", "x", "x", "x" },
            { "x", "x", "m", "x", "x", "x", "x", "x", "x", "x", "x" },
            { "x", "x", "x", "h", "x", "x", "x", "x", "x", "x", "x" },
            { "x", "x", "x", "m", "m", "x", "x", "x", "x", "x", "x" },
            { "x", "x", "x", "x", "x", "x", "x", "x", "x", "x", "x" }
        },
        {
            { "x", "x", "x", "x", "x", "x", "x", "h", "x", "x", "h" },
            { "x", "x", "x", "x", "x", "x", "x", "h", "x", "x", "x" },
            { "x", "x", "x", "x", "x", "x", "x", "h", "x", "x", "x" },
            { "x", "x", "x", "x", "x", "x", "x", "x", "x", "x", "x" },
            { "x", "x", "x", "x", "x", "x", "x", "x", "x", "x", "x" },
            { "h", "x", "x", "x", "x", "x", "x", "x", "x", "x", "x" }
        },
        {
            { "e", "x", "x", "x", "x", "x", "x", "x", "x", "x", "e" },
            { "x", "x", "x", "x", "x", "x", "x", "x", "x", "x", "x" },
            { "x", "x", "x", "x", "x", "x", "x", "x", "m", "x", "x" },
            { "x", "x", "x", "x", "x", "x", "x", "x", "x", "x", "x" },
            { "x", "x", "x", "x", "x", "x", "x", "x", "x", "h", "x" },
            { "x", "x", "x", "h", "x", "x", "x", "x", "x", "x", "x" }
        }
    }};

    void LevelBrickGridData::Initialize()
    {
        m_StringToBrickTypeMap = {
            {"x", BrickType::None},
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
                        brickGridDataArr[level].BrickGrid[row][col] = m_StringToBrickTypeMap[str];
                    }
                    else
                    {
                        LOG_ERROR("LEVELBRICKGRIDDATA | ConvertLevelBrickDataToBrickTypeMatrix | string to brick type map key not found: " + str);
                    }
                }
            }
        }
    }

    BrickType LevelBrickGridData::GetBrickType(std::string str)
    {
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
    }
}