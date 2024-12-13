#include "Brick.h"
namespace BreakoutGame
{
    void Brick::Initialize(std::shared_ptr<SpriteEntity> brickEntity, std::shared_ptr<BrickData> data)
    {
        m_Entity = brickEntity;
        m_Data = data;
        hitCount = 0;
    }
    void Brick::HandleOnBallHit()
    {
    }
    std::shared_ptr<SpriteEntity> Brick::getEntity()
    {
        return m_Entity;
    }
    std::shared_ptr<BrickData> Brick::getData()
    {
        return m_Data;
    }
    void Brick::Reset()
    {
        hitCount = 0;
    }
}
