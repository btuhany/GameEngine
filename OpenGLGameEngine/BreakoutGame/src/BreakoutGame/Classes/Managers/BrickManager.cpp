#include "BrickManager.h"
namespace BreakoutGame
{
	void BrickManager::Initialize(std::shared_ptr<Shader> mainShader, std::function<void()> onThereIsNoActiveBricksLeftHandler)
	{
		m_OnEnterAnimationEnd = nullptr;
		m_IsEnterAnimationPlaying = false;
		m_AnimationLerpValue = 0.0f;
		m_ActiveBrickCount = 0;
		m_OnThereIsNoActiveBricksLeft = onThereIsNoActiveBricksLeftHandler;

		initializeEasyBrickData(mainShader);
		initializeMediumBrickData(mainShader);
		initializeHardBrickData(mainShader);

		std::shared_ptr<Texture> initialBrickTexture = std::make_shared<Texture>("src/BreakoutGame/Textures/17-Breakout-Tiles.PNG");
		initialBrickTexture->LoadTextureWithAlpha();
		std::shared_ptr<SpriteRenderData> initalSpriteRenderData = std::make_shared<SpriteRenderData>(initialBrickTexture, nullptr, mainShader);

		PoolBricks();
	}
	void BrickManager::PoolBricks()
	{
		for (int y = 0; y < ROW_SIZE; y++)
		{
			std::vector <std::shared_ptr<Brick>> rowBrickList;
			for (int x = 0; x < COLUMN_SIZE; x++)
			{
				std::string name = "Brick_" + std::to_string(y) + "_" + std::to_string(x);
				auto brick = std::make_shared<Brick>();

				//TODO Init data
				auto easyBrickData = GetBrickData(BrickType::Easy);
				brick->Initialize(name, easyBrickData);

				auto pos = Vector2(START_POS.x + x * SPACING.x, START_POS.y - y * SPACING.y);
				brick->SetPosition(pos);

				rowBrickList.push_back(brick);
			}
			m_BrickGrid.push_back(rowBrickList);
		}
	}

	void BrickManager::HandleOnAfterBricksInstantiated()
	{
		auto entityList = getEntityList();
		for (size_t i = 0; i < entityList.size(); i++)
		{
			entityList[i]->setActive(false);
		}
	}
	void BrickManager::Reset()
	{
		m_ActiveBrickCount = 0;
	}
	void BrickManager::Tick(float deltaTime)
	{
		if (m_IsEnterAnimationPlaying)
		{
			m_AnimationLerpValue += deltaTime;;
			m_AnimationLerpValue = std::min(m_AnimationLerpValue, 1.0f);

			if (m_AnimationLerpValue >= 1.0f)
			{
				finalizeEnterAnimation();
				m_IsEnterAnimationPlaying = false;
				if (m_OnEnterAnimationEnd != nullptr)
				{
					m_OnEnterAnimationEnd();
					m_OnEnterAnimationEnd = nullptr;
				}
			}
			else
			{
				tickHandleEnterAnimation(m_AnimationLerpValue);
			}
		}
	}
	void BrickManager::UpdateBrickGrid(BrickGridData brickTypeGridData)
	{
		m_ActiveBrickCount = 0;
		for (size_t row = 0; row < ROW_SIZE; row++)
		{
			for (size_t col = 0; col < COLUMN_SIZE; col++)
			{
				auto type = brickTypeGridData.grid[row][col];
				auto brick = m_BrickGrid[row][col];

				if (type == BrickType::None)
				{
					brick->getEntity()->setActive(false);
				}
				else
				{
					m_ActiveBrickCount++;
					brick->getEntity()->setActive(true);
					brick->ResetUpdateData(GetBrickData(type));
				}
			}
		}
	}
	void BrickManager::PlayBrickGridEnterAnimation(std::function<void()> onAnimationEndCallback)
	{
		m_OnEnterAnimationEnd = onAnimationEndCallback;
		m_IsEnterAnimationPlaying = true;
		for (size_t row = 0; row < ROW_SIZE; row++)
		{
			for (size_t col = 0; col < COLUMN_SIZE; col++)
			{
				auto brick = m_BrickGrid[row][col];
				if (brick->getType() != BrickType::None)
				{
					auto position = VectorUtility::GlmVec3ToVector3(brick->getEntity()->transform->getPosition());
					Vector3 startOffset = Vector3(0.0f, -50.0f, 0.0f);
					brick->InitializeEnterAnimStart(position + startOffset);
				}
			}
		}
	}
	void BrickManager::tickHandleEnterAnimation(float animationLerpValue)
	{
		for (size_t row = 0; row < ROW_SIZE; row++)
		{
			for (size_t col = 0; col < COLUMN_SIZE; col++)
			{
				auto brick = m_BrickGrid[row][col];
				if (brick->getType() != BrickType::None)
				{
					float lerpValue = TweenEase::EaseOutBack(animationLerpValue);
					brick->TickAnimation(lerpValue);
				}
			}
		}
	}
	void BrickManager::finalizeEnterAnimation()
	{
		for (size_t row = 0; row < ROW_SIZE; row++)
		{
			for (size_t col = 0; col < COLUMN_SIZE; col++)
			{
				auto brick = m_BrickGrid[row][col];
				if (brick->getType() != BrickType::None)
				{
					brick->StopAnimationResetPos();
				}
			}
		}
	}
	std::vector<std::shared_ptr<GameEntity>> BrickManager::getEntityList()
	{
		auto entities = std::vector<std::shared_ptr<GameEntity>>();
		for (size_t i = 0; i < m_BrickGrid.size(); i++)
		{
			auto rowList = m_BrickGrid[i];
			for (size_t j = 0; j < rowList.size(); j++)
			{
				entities.push_back(rowList[j]->getEntity());
			}
		}
		return entities;
	}
	BallHitBrickData BrickManager::HandleOnGotHitByBall(std::shared_ptr<GameEntity> brickEntity)
	{
		auto brick = findBrick(brickEntity);
		if (brick == nullptr)
		{
			LOG_ERROR("BRICK MANAGER | HandleOnGotHitByBall | Brick is null!");
			return BallHitBrickData();
		}
		
		return processBrick(brick);
	}
	BallHitBrickData BrickManager::processBrick(std::shared_ptr<Brick> brick)
	{
		if (!brick->getEntity()->getActive())
		{
			LOG_ERROR("processBrick | brick object not active!");
		}
		BallHitBrickData hitData;

		auto brickData = GetBrickData(brick->getType());
		brick->hitCount++;

		hitData.gainedScorePoint = brickData->scorePointOnHit;

		if (brick->hitCount == brickData->hitCountToBreak)
		{
			hitData.gainedScorePoint += brickData->scorePointOnBreak;
			hitData.isBroken = true;
			brick->getEntity()->setActive(false);
			m_ActiveBrickCount--;
			if (m_ActiveBrickCount == 0)
			{
				m_OnThereIsNoActiveBricksLeft();
			}
		}
		else
		{
			hitData.isBroken = false;
			brick->UpdateSprite(brickData->spriteRenderDataListOrderedHitCountAscending[brick->hitCount]);
		}

		return hitData;
	}
	std::shared_ptr<BrickData> BrickManager::GetBrickData(BrickType brickType)
	{
		return m_BrickDataMap[brickType];
	}
	std::shared_ptr<Brick> BrickManager::findBrick(std::shared_ptr<GameEntity> brickEntity)
	{
		std::shared_ptr<Brick> brick = nullptr;
		//FIND BRICK
		for (size_t i = 0; i < m_BrickGrid.size(); i++)
		{
			auto rowList = m_BrickGrid[i];
			for (size_t j = 0; j < rowList.size(); j++)
			{
				if (rowList[j]->getEntity() == brickEntity)
				{
					brick = rowList[j];
					break;
				}
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
		easyBrickData->brickType = BrickType::Easy;

		std::shared_ptr<Texture> brickTexture = std::make_shared<Texture>("src/BreakoutGame/Textures/03-Breakout-Tiles.PNG");
		brickTexture->LoadTextureWithAlpha();
		std::shared_ptr<SpriteRenderData> brickSpriteRenderData = std::make_shared<SpriteRenderData>(brickTexture, nullptr, shader);
		easyBrickData->spriteRenderDataListOrderedHitCountAscending.push_back(brickSpriteRenderData);

		m_BrickDataMap[BrickType::Easy] = easyBrickData;
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
		mediumBrickData->brickType = BrickType::Medium;

		std::shared_ptr<Texture> brickTexture = std::make_shared<Texture>("src/BreakoutGame/Textures/05-Breakout-Tiles.PNG");
		brickTexture->LoadTextureWithAlpha();
		std::shared_ptr<SpriteRenderData> brickSpriteRenderData = std::make_shared<SpriteRenderData>(brickTexture, nullptr, shader);
		mediumBrickData->spriteRenderDataListOrderedHitCountAscending.push_back(brickSpriteRenderData);

		std::shared_ptr<Texture> brokenBrickTexture = std::make_shared<Texture>("src/BreakoutGame/Textures/06-Breakout-Tiles.PNG");
		brokenBrickTexture->LoadTextureWithAlpha();
		std::shared_ptr<SpriteRenderData> brokenSpriteRenderData = std::make_shared<SpriteRenderData>(brokenBrickTexture, nullptr, shader);
		mediumBrickData->spriteRenderDataListOrderedHitCountAscending.push_back(brokenSpriteRenderData);

		m_BrickDataMap[BrickType::Medium] = mediumBrickData;
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
		hardBrickData->brickType = BrickType::Hard;

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

		m_BrickDataMap[BrickType::Hard] = hardBrickData;
	}

}