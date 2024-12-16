#include "BrickManager.h"
namespace BreakoutGame
{
	void BrickManager::Initialize(std::shared_ptr<Shader> mainShader)
	{
		initializeEasyBrickData(mainShader);
		initializeMediumBrickData(mainShader);
		initializeHardBrickData(mainShader);


		std::shared_ptr<Texture> initialBrickTexture = std::make_shared<Texture>("src/BreakoutGame/Textures/17-Breakout-Tiles.PNG");
		initialBrickTexture->LoadTextureWithAlpha();
		std::shared_ptr<SpriteRenderData> initalSpriteRenderData = std::make_shared<SpriteRenderData>(initialBrickTexture, nullptr, mainShader);


		for (int y = ROW_SIZE - 1; y >= 0; y--)
		{
			for (int x = 0; x < COLUMN_SIZE; x++)
			{
				std::string name = "Brick_" + std::to_string(y) + "_" + std::to_string(x);
				auto brick = std::make_shared<Brick>();
				brick->Initialize(name, initalSpriteRenderData, BrickType::Easy);

				auto pos = Vector2(START_POS.x + x * SPACING.x, START_POS.y + y * SPACING.y);
				brick->SetPosition(pos);

				m_BrickList.push_back(brick);
			}
		}
	}
	std::vector<std::shared_ptr<GameEntity>> BrickManager::getEntityList()
	{
		auto entities = std::vector<std::shared_ptr<GameEntity>>();
		for (size_t i = 0; i < m_BrickList.size(); i++)
		{
			entities.push_back(m_BrickList[i]->getEntity());
		}
		return entities;
	}
	BallHitBrickData BrickManager::HandleOnGotHitByBall(std::shared_ptr<GameEntity> brickEntity)
	{
		BallHitBrickData hitData;
		auto brick = findBrick(brickEntity);
		if (brick == nullptr)
		{
			LOG_ERROR("BRICK MANAGER | HandleOnGotHitByBall | Brick is null!");
			return hitData;
		}

		hitData.gainedScorePoint = 1;
		LOG_INFO("BRICK GOT HIT, NAME: " + brick->getEntity()->getName());
		brick->getEntity()->setActive(false);
		return hitData;
	}
	std::shared_ptr<Brick> BrickManager::findBrick(std::shared_ptr<GameEntity> brickEntity)
	{
		std::shared_ptr<Brick> brick = nullptr;
		//FIND BRICK
		for (size_t i = 0; i < m_BrickList.size(); i++)
		{
			if (m_BrickList[i]->getEntity() == brickEntity)
			{
				brick = m_BrickList[i];
				break;
			}
		}
		return brick;
	}
	void BrickManager::initializeEasyBrickData(std::shared_ptr<Shader> shader)
	{
		m_EasyBrickData = std::make_shared<BrickData>();
		m_EasyBrickData->hitCountToBreak = 1;
		m_EasyBrickData->scorePointOnHit = 0;
		m_EasyBrickData->scorePointOnBreak = 10;
		m_EasyBrickData->isAbleToDropHealthPoint = false;
		m_EasyBrickData->isAbleToDropPerk = false;
		m_EasyBrickData->isAbleToDropExtraScorePoint = false;

		std::shared_ptr<Texture> brickTexture = std::make_shared<Texture>("src/BreakoutGame/Textures/03-Breakout-Tiles.PNG");
		brickTexture->LoadTextureWithAlpha();
		std::shared_ptr<SpriteRenderData> brickSpriteRenderData = std::make_shared<SpriteRenderData>(brickTexture, nullptr, shader);
		m_EasyBrickData->spriteRenderDataListOrderedHitCountAscending.push_back(brickSpriteRenderData);
	}
	void BrickManager::initializeMediumBrickData(std::shared_ptr<Shader> shader)
	{
		m_MediumBrickData = std::make_shared<BrickData>();
		m_MediumBrickData->hitCountToBreak = 2;
		m_MediumBrickData->scorePointOnHit = 5;
		m_MediumBrickData->scorePointOnBreak = 10;
		m_MediumBrickData->isAbleToDropHealthPoint = false;
		m_MediumBrickData->isAbleToDropPerk = false;
		m_MediumBrickData->isAbleToDropExtraScorePoint = false;

		std::shared_ptr<Texture> brickTexture = std::make_shared<Texture>("src/BreakoutGame/Textures/05-Breakout-Tiles.PNG");
		brickTexture->LoadTextureWithAlpha();
		std::shared_ptr<SpriteRenderData> brickSpriteRenderData = std::make_shared<SpriteRenderData>(brickTexture, nullptr, shader);
		m_MediumBrickData->spriteRenderDataListOrderedHitCountAscending.push_back(brickSpriteRenderData);

		std::shared_ptr<Texture> brokenBrickTexture = std::make_shared<Texture>("src/BreakoutGame/Textures/06-Breakout-Tiles.PNG");
		brokenBrickTexture->LoadTextureWithAlpha();
		std::shared_ptr<SpriteRenderData> brokenSpriteRenderData = std::make_shared<SpriteRenderData>(brokenBrickTexture, nullptr, shader);
		m_MediumBrickData->spriteRenderDataListOrderedHitCountAscending.push_back(brokenSpriteRenderData);
	}
	void BrickManager::initializeHardBrickData(std::shared_ptr<Shader> shader)
	{
		m_HardBrickData = std::make_shared<BrickData>();
		m_HardBrickData->hitCountToBreak = 3;
		m_HardBrickData->scorePointOnHit = 5;
		m_HardBrickData->scorePointOnBreak = 15;
		m_HardBrickData->isAbleToDropHealthPoint = false;
		m_HardBrickData->isAbleToDropPerk = false;
		m_HardBrickData->isAbleToDropExtraScorePoint = false;

		std::shared_ptr<Texture> brickTexture = std::make_shared<Texture>("src/BreakoutGame/Textures/07-Breakout-Tiles.PNG");
		brickTexture->LoadTextureWithAlpha();
		std::shared_ptr<SpriteRenderData> brickSpriteRenderData = std::make_shared<SpriteRenderData>(brickTexture, nullptr, shader);
		m_HardBrickData->spriteRenderDataListOrderedHitCountAscending.push_back(brickSpriteRenderData);

		std::shared_ptr<Texture> brokenBrickTexture = std::make_shared<Texture>("src/BreakoutGame/Textures/08-Breakout-Tiles.PNG");
		brokenBrickTexture->LoadTextureWithAlpha();
		std::shared_ptr<SpriteRenderData> brokenSpriteRenderData = std::make_shared<SpriteRenderData>(brokenBrickTexture, nullptr, shader);
		m_HardBrickData->spriteRenderDataListOrderedHitCountAscending.push_back(brokenSpriteRenderData);

		std::shared_ptr<Texture> broken2BrickTexture = std::make_shared<Texture>("src/BreakoutGame/Textures/081-Breakout-Tiles.PNG");
		broken2BrickTexture->LoadTextureWithAlpha();
		std::shared_ptr<SpriteRenderData> broken2SpriteRenderData = std::make_shared<SpriteRenderData>(broken2BrickTexture, nullptr, shader);
		m_HardBrickData->spriteRenderDataListOrderedHitCountAscending.push_back(broken2SpriteRenderData);
	}

}