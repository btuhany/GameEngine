#include "PerkManager.h"
namespace BreakoutGame
{
	void PerkManager::Initialize(std::shared_ptr<Shader> shader)
	{
		poolPerks(shader);
		initializePerkSpriteRenderDataMap(shader);
		initCumulativePerkTypeProbabilities();
		//printProbabilities();
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
	void PerkManager::HandleOnBallHitBrick(BallHitBrickData hitData, BrickData brickData)
	{
		if (hitData.isBroken)
		{
			if (brickData.perkDropRateOnBreak <= 0.0f)
				return;
		}
		else
		{
			if (brickData.perkDropRateOnHit <= 0.0f)
				return;
		}


		int randomNumber = RandomGenerator::GetInt(1, 100);
		int probabilityNumber = 100 * brickData.perkDropRateOnHit;
		if (probabilityNumber < randomNumber)
			return;

		trySpawnPerk(hitData.brickPos);
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
	float PerkManager::getPerkProbability(PerkType perkType, float multiplier)
	{
		return m_PerkProbabilityMap.at(perkType) * multiplier;
	}
	void PerkManager::trySpawnPerk(Vector3 pos)
	{
		//Try get inactive entity
		std::shared_ptr<Perk> perk = nullptr;
		for (size_t i = 0; i < m_PerkPool.size(); i++)
		{
			auto entity = m_PerkPool[i]->getEntity();
			if (!entity->getActive())
			{
				perk = m_PerkPool[i];
				break;
			}
		}

		if (perk == nullptr)
			return;

		//BAD PRACTICE
		
		PerkType perkType = getRandomPerkType();
		if (perkType == PerkType::None)
		{
			LOG_ERROR("trySpawnPerk | getRandomPerkType | perk type is null");
			return;
		}
		auto perkEntity = perk->getEntity();
		perkEntity->transform->SetPosition(pos);
		perk->UpdateData(perkType, m_PerkSpriteRenderDataMap[perkType]);
		perkEntity->setActive(true);
	}
	void PerkManager::initializePerkSpriteRenderDataMap(std::shared_ptr<Shader> shader)
	{
		std::shared_ptr<Texture> tex = std::make_shared<Texture>("src/BreakoutGame/Textures/60-Breakout-Tiles.PNG");
		tex->LoadTextureWithAlpha();
		m_PerkSpriteRenderDataMap[PerkType::IncreaseLive] = std::make_shared<SpriteRenderData>(tex, nullptr, shader);

		tex = std::make_shared<Texture>("src/BreakoutGame/Textures/43-Breakout-Tiles.PNG");
		tex->LoadTextureWithAlpha();
		m_PerkSpriteRenderDataMap[PerkType::ThreeBall] = std::make_shared<SpriteRenderData>(tex, nullptr, shader);

		tex = std::make_shared<Texture>("src/BreakoutGame/Textures/47-Breakout-Tiles.PNG");
		tex->LoadTextureWithAlpha();
		m_PerkSpriteRenderDataMap[PerkType::PaddleScaleUp] = std::make_shared<SpriteRenderData>(tex, nullptr, shader);

		tex = std::make_shared<Texture>("src/BreakoutGame/Textures/46-Breakout-Tiles.PNG");
		tex->LoadTextureWithAlpha();
		m_PerkSpriteRenderDataMap[PerkType::PaddleScaleDown] = std::make_shared<SpriteRenderData>(tex, nullptr, shader);

		tex = std::make_shared<Texture>("src/BreakoutGame/Textures/42-Breakout-Tiles.PNG");
		tex->LoadTextureWithAlpha();
		m_PerkSpriteRenderDataMap[PerkType::PaddleSpeedUp] = std::make_shared<SpriteRenderData>(tex, nullptr, shader);

		tex = std::make_shared<Texture>("src/BreakoutGame/Textures/41-Breakout-Tiles.PNG");
		tex->LoadTextureWithAlpha();
		m_PerkSpriteRenderDataMap[PerkType::PaddleSpeedDown] = std::make_shared<SpriteRenderData>(tex, nullptr, shader);
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
	PerkType PerkManager::getRandomPerkType()
	{
		PerkType perkType = PerkType::None;
		int randomNumber = RandomGenerator::GetInt(1, 100);
		for (size_t i = 0; i < m_CumulativePerkTypeProbabilityList.size(); i++)
		{
			if (randomNumber <= m_CumulativePerkTypeProbabilityList[i] * 100.0f)
			{
				perkType = m_AllPerkTypeArr[i];
				break;
			}
		}
		return perkType;
	}
	void PerkManager::initCumulativePerkTypeProbabilities()
	{
		float cumulativeSum = 0.0f;
		for (const auto& perk : m_AllPerkTypeArr) {
			float probability = m_PerkProbabilityMap.at(perk);
			cumulativeSum += probability;
			m_CumulativePerkTypeProbabilityList.push_back(cumulativeSum);
		}
	}
	void PerkManager::printProbabilities()
	{
		std::unordered_map<int, int> numberMap;
		for (size_t i = 0; i < 100; i++)
		{
			PerkType perkType = PerkType::None;
			int randomNumber = RandomGenerator::GetInt(1, 100);
			for (size_t i = 0; i < m_CumulativePerkTypeProbabilityList.size(); i++)
			{
				if (randomNumber <= m_CumulativePerkTypeProbabilityList[i] * 100.0f)
				{
					perkType = m_AllPerkTypeArr[i];
					if (numberMap.find(i) != numberMap.end())
					{
						numberMap[i]++;
					}
					else
					{
						numberMap[i] = 1;
					}
					break;
				}
			}
		}
		for (const auto& pair : numberMap) {
			LOG_ERROR("\n index: " + std::to_string(pair.first) + " , count: " + std::to_string(pair.second));
		}
	}
}