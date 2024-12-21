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
		auto boxCollider2DComp = std::make_shared<BoxCollider2DComponent>(3.0f, 3.0f, CollisionType::Static);
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
	}
	std::shared_ptr<SpriteEntity> Perk::getEntity()
	{
		return m_Entity;
	}
	PerkType Perk::getType()
	{
		return m_Type;
	}
	void Perk::MoveLeft()
	{
	}
	void Perk::MoveRight()
	{
	}
	void Perk::MoveUp()
	{
	}
	void Perk::MoveDown()
	{
	}
}