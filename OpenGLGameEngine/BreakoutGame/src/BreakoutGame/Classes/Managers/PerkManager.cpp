#include "PerkManager.h"
namespace BreakoutGame
{
	void PerkManager::Initialize(std::shared_ptr<Shader> shader)
	{
		poolPerks(shader);
		initializePerkSpriteRenderDataMap(shader);
	}
	void PerkManager::Start()
	{
		for (size_t i = 0; i < m_PerkPool.size(); i++)
		{
			m_PerkPool[i]->Start();
		}
	}
	void PerkManager::Tick(float deltaTime)
	{
		for (size_t i = 0; i < m_PerkPool.size(); i++)
		{
			m_PerkPool[i]->Tick(deltaTime);
		}
	}
	std::vector<std::shared_ptr<GameEntity>> PerkManager::getEntityList()
	{
		auto entityList = std::vector<std::shared_ptr<GameEntity>>();
		for (size_t i = 0; i < m_PerkPool.size(); i++)
		{
			entityList.push_back(m_PerkPool[i]->getEntity());
		}
		return entityList;
	}
	void PerkManager::HandleOnBallHitBrick(BallHitBrickData hitData)
	{

	}
	void PerkManager::HandleOnLevelInit()
	{
		for (size_t i = 0; i < m_PerkPool.size(); i++)
		{
			auto perkEntity = m_PerkPool[i]->getEntity();
			if (perkEntity->getActive())
				perkEntity->setActive(false);
		}
	}
	void PerkManager::initializePerkSpriteRenderDataMap(std::shared_ptr<Shader> shader)
	{
		loadSpriteIncreaseLiveToMap(shader);
	}
	void PerkManager::loadSpriteIncreaseLiveToMap(std::shared_ptr<Shader> shader)
	{
		std::shared_ptr<Texture> tex = std::make_shared<Texture>("src/BreakoutGame/Textures/60-Breakout-Tiles.PNG");
		tex->LoadTextureWithAlpha();
		std::shared_ptr<SpriteRenderData> spriteRenderData = std::make_shared<SpriteRenderData>(tex, nullptr, shader);
		m_PerkSpriteRenderDataMap[PerkType::IncreaseLive] = spriteRenderData;
	}
	void PerkManager::poolPerks(std::shared_ptr<Shader> shader)
	{
		for (size_t i = 0; i < MAX_PERK_COUNT_INGAME; i++)
		{
			std::string name = "Perk_" + std::to_string(i);
			auto perk = std::make_shared<Perk>();
			perk->CreateEntity(shader);
			m_PerkPool.push_back(perk);
		}
	}
}