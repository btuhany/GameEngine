#include "Brick.h"
namespace BreakoutGame
{
    void Brick::Initialize(std::string entityName, std::shared_ptr<BrickProperties> brickData)
    {
        hitCount = 0;
        m_Entity = std::make_shared<SpriteEntity>(brickData->spriteRenderDataListOrderedHitCountAscending[hitCount]);
        m_Entity->setName(entityName);
        m_Entity->setTag((int)Tag::Brick);
        auto boxCollider2DComp = std::make_shared<BoxCollider2DComponent>(6.0f, 2.0f, CollisionType::Static);
        m_Entity->AddComponent<BoxCollider2DComponent>(boxCollider2DComp);
        m_Entity->transform->SetPosition(glm::vec3(0.0f, 0.0f, -0.5f));
        m_Type = brickData->brickType;
    }
    void Brick::ResetUpdateData(std::shared_ptr<BrickProperties> brickData)
    {
        hitCount = 0;
        m_Type = brickData->brickType;
        UpdateSprite(brickData->spriteRenderDataListOrderedHitCountAscending[hitCount]);
    }
    void Brick::UpdateSprite(std::shared_ptr<SpriteRenderData> spriteRenderData)
    {
        m_Entity->renderer->setSpriteRenderData(spriteRenderData);
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
    void Brick::TickAnimation(float lerpValue)
    {
        auto newPos = Vector3::UnclampedLerp(m_EnterAnimStartPosition, m_EnterAnimStopPosition, lerpValue);
        m_Entity->transform->SetPosition(newPos);
    }
    void Brick::InitializeEnterAnimStart(Vector3 startPos)
    {
        m_EnterAnimStopPosition = VectorUtility::GlmVec3ToVector3(m_Entity->transform->getPosition());
        m_EnterAnimStartPosition = startPos;
        m_Entity->transform->SetPosition(m_EnterAnimStartPosition);
    }
    void Brick::StopAnimationResetPos()
    {
        m_Entity->transform->SetPosition(m_EnterAnimStopPosition);
    }
}
