#include "Brick.h"
namespace BreakoutGame
{
    void Brick::Initialize(std::shared_ptr<SpriteEntity> brickEntity, std::shared_ptr<SpriteRenderData> initialRenderData, BrickType type)
    {
        m_Entity = brickEntity;
        m_Type = type;
        hitCount = 0;
    }
    void Brick::UpdateSprite(std::shared_ptr<SpriteRenderData> spriteRenderData)
    {
        m_Entity->renderer->setSpriteRenderData(spriteRenderData);
    }
    void Brick::UpdateType(BrickType brickType)
    {
        m_Type = brickType;
    }
    void Brick::HandleOnBallHit()
    {
    }
    std::shared_ptr<SpriteEntity> Brick::getEntity()
    {
        return m_Entity;
    }
    BrickType Brick::getType()
    {
        return m_Type;
    }
    void Brick::ResetHitCount()
    {
        hitCount = 0;
    }
}
