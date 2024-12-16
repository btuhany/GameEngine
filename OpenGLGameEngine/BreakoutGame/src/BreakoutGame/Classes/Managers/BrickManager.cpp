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

				auto easyBrickData = GetBrickData(BrickType::Easy);
				auto mediumBrickData = GetBrickData(BrickType::Medium);

				//TODO
				if (x > COLUMN_SIZE / 2)
				{
					brick->Initialize(name, easyBrickData);
				}
				else
				{
					brick->Initialize(name, mediumBrickData);
				}

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
		
		hitData = processBrick(brick);
		return hitData;
	}
	BallHitBrickData BrickManager::processBrick(std::shared_ptr<Brick> brick)
	{
		BallHitBrickData hitData;

		auto brickData = GetBrickData(brick->getType());
		brick->hitCount++;

		hitData.gainedScorePoint = brickData->scorePointOnHit;

		if (brick->hitCount == brickData->hitCountToBreak)
		{
			hitData.gainedScorePoint += brickData->scorePointOnBreak;
			brick->getEntity()->setActive(false);
		}
		else
		{
			brick->UpdateSprite(brickData->spriteRenderDataListOrderedHitCountAscending[brick->hitCount]);
		}

		return hitData;
	}
	std::shared_ptr<BrickData> BrickManager::GetBrickData(BrickType brickType)
	{
		for (size_t i = 0; i < m_BrickDataList.size(); i++)
		{
			if (m_BrickDataList[i]->type == brickType) 
			{
				return m_BrickDataList[i];
			}
		}
		return nullptr;
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
		auto easyBrickData = std::make_shared<BrickData>();
		easyBrickData->hitCountToBreak = 1;
		easyBrickData->scorePointOnHit = 0;
		easyBrickData->scorePointOnBreak = 10;
		easyBrickData->isAbleToDropHealthPoint = false;
		easyBrickData->isAbleToDropPerk = false;
		easyBrickData->isAbleToDropExtraScorePoint = false;
		easyBrickData->type = BrickType::Easy;

		std::shared_ptr<Texture> brickTexture = std::make_shared<Texture>("src/BreakoutGame/Textures/03-Breakout-Tiles.PNG");
		brickTexture->LoadTextureWithAlpha();
		std::shared_ptr<SpriteRenderData> brickSpriteRenderData = std::make_shared<SpriteRenderData>(brickTexture, nullptr, shader);
		easyBrickData->spriteRenderDataListOrderedHitCountAscending.push_back(brickSpriteRenderData);

		m_BrickDataList.push_back(easyBrickData);
	}
	void BrickManager::initializeMediumBrickData(std::shared_ptr<Shader> shader)
	{
		auto mediumBrickData = std::make_shared<BrickData>();
		mediumBrickData->hitCountToBreak = 2;
		mediumBrickData->scorePointOnHit = 5;
		mediumBrickData->scorePointOnBreak = 10;
		mediumBrickData->isAbleToDropHealthPoint = false;
		mediumBrickData->isAbleToDropPerk = false;
		mediumBrickData->isAbleToDropExtraScorePoint = false;
		mediumBrickData->type = BrickType::Medium;

		std::shared_ptr<Texture> brickTexture = std::make_shared<Texture>("src/BreakoutGame/Textures/05-Breakout-Tiles.PNG");
		brickTexture->LoadTextureWithAlpha();
		std::shared_ptr<SpriteRenderData> brickSpriteRenderData = std::make_shared<SpriteRenderData>(brickTexture, nullptr, shader);
		mediumBrickData->spriteRenderDataListOrderedHitCountAscending.push_back(brickSpriteRenderData);

		std::shared_ptr<Texture> brokenBrickTexture = std::make_shared<Texture>("src/BreakoutGame/Textures/06-Breakout-Tiles.PNG");
		brokenBrickTexture->LoadTextureWithAlpha();
		std::shared_ptr<SpriteRenderData> brokenSpriteRenderData = std::make_shared<SpriteRenderData>(brokenBrickTexture, nullptr, shader);
		mediumBrickData->spriteRenderDataListOrderedHitCountAscending.push_back(brokenSpriteRenderData);

		m_BrickDataList.push_back(mediumBrickData);
	}
	void BrickManager::initializeHardBrickData(std::shared_ptr<Shader> shader)
	{
		auto hardBrickData = std::make_shared<BrickData>();
		hardBrickData->hitCountToBreak = 3;
		hardBrickData->scorePointOnHit = 5;
		hardBrickData->scorePointOnBreak = 15;
		hardBrickData->isAbleToDropHealthPoint = false;
		hardBrickData->isAbleToDropPerk = false;
		hardBrickData->isAbleToDropExtraScorePoint = false;
		hardBrickData->type = BrickType::Hard;

		std::shared_ptr<Texture> brickTexture = std::make_shared<Texture>("src/BreakoutGame/Textures/07-Breakout-Tiles.PNG");
		brickTexture->LoadTextureWithAlpha();
		std::shared_ptr<SpriteRenderData> brickSpriteRenderData = std::make_shared<SpriteRenderData>(brickTexture, nullptr, shader);
		hardBrickData->spriteRenderDataListOrderedHitCountAscending.push_back(brickSpriteRenderData);

		std::shared_ptr<Texture> brokenBrickTexture = std::make_shared<Texture>("src/BreakoutGame/Textures/08-Breakout-Tiles.PNG");
		brokenBrickTexture->LoadTextureWithAlpha();
		std::shared_ptr<SpriteRenderData> brokenSpriteRenderData = std::make_shared<SpriteRenderData>(brokenBrickTexture, nullptr, shader);
		hardBrickData->spriteRenderDataListOrderedHitCountAscending.push_back(brokenSpriteRenderData);

		std::shared_ptr<Texture> broken2BrickTexture = std::make_shared<Texture>("src/BreakoutGame/Textures/081-Breakout-Tiles.PNG");
		broken2BrickTexture->LoadTextureWithAlpha();
		std::shared_ptr<SpriteRenderData> broken2SpriteRenderData = std::make_shared<SpriteRenderData>(broken2BrickTexture, nullptr, shader);
		hardBrickData->spriteRenderDataListOrderedHitCountAscending.push_back(broken2SpriteRenderData);

		m_BrickDataList.push_back(hardBrickData);
	}

}