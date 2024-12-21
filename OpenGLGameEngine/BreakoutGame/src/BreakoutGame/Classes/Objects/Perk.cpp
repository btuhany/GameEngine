#include "Perk.h"
namespace BreakoutGame
{
	std::string ToString(PerkType type)
	{
		switch (type)
		{
		case PerkType::None:
			return "None";
		case PerkType::IncreaseLive:
			return "IncreaseLive";
		default:
			return "Unknown";
		}
	}

	void Perk::CreateEntity(std::shared_ptr<Shader> shader)
	{
		std::shared_ptr<Texture> tex = std::make_shared<Texture>("src/BreakoutGame/Textures/21-Breakout-Tiles.PNG");
		tex->LoadTextureWithAlpha();
		std::shared_ptr<SpriteRenderData> initialSprite = std::make_shared<SpriteRenderData>(tex, nullptr, shader);

		m_Type = PerkType::None;
		m_Entity = std::make_shared<SpriteEntity>(initialSprite);
		m_Entity->setName(ToString(m_Type));
		m_Entity->setTag((int)Tag::Perk);

		auto detector = std::make_shared<CollisionDetector>();
		auto boxCollider2DComp = std::make_shared<BoxCollider2DComponent>(2.0f, 2.0f, CollisionType::Dynamic, detector);
		detector->AddCollisionCallback(CollisionState::Enter,
			[this](std::shared_ptr<CollisionData> collider) {
				onCollisionEnter(collider);
			});



		m_Entity->AddComponent<BoxCollider2DComponent>(boxCollider2DComp);
		m_Entity->transform->SetPosition(glm::vec3(0.0f, 0.0f, -0.5f));
	}
	void Perk::UpdateData(PerkType perkType, std::shared_ptr<SpriteRenderData> spriteRenderData)
	{
		m_Type = perkType;
	}
	void Perk::Start()
	{
		m_Entity->setActive(true);
	}
	void Perk::Tick(float deltaTime)
	{
		if (!m_Entity->getActive())
			return;
		MoveDown(deltaTime);
	}
	std::shared_ptr<SpriteEntity> Perk::getEntity()
	{
		return m_Entity;
	}
	PerkType Perk::getType()
	{
		return m_Type;
	}
	void Perk::MoveDown(float deltaTime)
	{
		auto downVector = glm::vec3(0.0f, -1.0f, 0.0f);
		m_Entity->transform->Translate(downVector * SPEED * deltaTime);
	}
	void Perk::onCollisionEnter(std::shared_ptr<CollisionData> collisionData)
	{
		auto otherCollider = collisionData->otherCollider;
		auto colliderEntityWeakPtr = otherCollider->getEntity();
		if (colliderEntityWeakPtr.expired())
		{
			LOG_ERROR("Perk | onCollisionEnter | Entity is expired!");
			return;
		}
		auto colliderEntity = colliderEntityWeakPtr.lock();
		
		if (colliderEntity->getTag() != (int)Tag::Brick)
		{
			m_Entity->setActive(false);
		}
	}
}