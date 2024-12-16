#include "Brick.h"
namespace BreakoutGame
{
    void Brick::Initialize(std::string entityName, std::shared_ptr<BrickData> brickData)
    {
        hitCount = 0;
        m_Entity = std::make_shared<SpriteEntity>(brickData->spriteRenderDataListOrderedHitCountAscending[hitCount]);
        m_Entity->setName(entityName);
        m_Entity->setTag((int)Tag::Brick);
        auto boxCollider2DComp = std::make_shared<BoxCollider2DComponent>(6.0f, 2.0f, CollisionType::Static);
        m_Entity->AddComponent<BoxCollider2DComponent>(boxCollider2DComp);
        m_Entity->transform->SetPosition(glm::vec3(0.0f, 0.0f, -0.5f));
    }
    void Brick::UpdateSprite(std::shared_ptr<SpriteRenderData> spriteRenderData)
    {
        m_Entity->renderer->setSpriteRenderData(spriteRenderData);
    }
    void Brick::UpdateType(BrickType brickType)
    {
        m_Type = brickType;
    }
    void Brick::SetPosition(Vector2 pos)
    {
        m_Entity->transform->SetPosition(
            glm::vec3(pos.x,
                pos.y,
                m_Entity->transform->getPosition().z)
        );
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
