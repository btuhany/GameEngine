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


		for (size_t y = ROW_SIZE; y > 0; y--)
		{
			for (size_t x = 0; x < COLUMN_SIZE; x++)
			{
				std::shared_ptr<SpriteEntity> spriteEntity = std::make_shared<SpriteEntity>(initalSpriteRenderData);

				std::string name = "Brick_" + std::to_string(y) + "_" + std::to_string(x);
				spriteEntity->setName(name);


				spriteEntity->transform->SetPosition(glm::vec3(x * SPACING.x, y * SPACING.y, -0.5f));
				auto boxCollider2DComp = std::make_shared<BoxCollider2DComponent>(6.0f, 2.0f, CollisionType::Static);
				spriteEntity->AddComponent<BoxCollider2DComponent>(boxCollider2DComp);
				m_CurrentBricks.push_back(spriteEntity);
			}
		}
	}
	std::vector<std::shared_ptr<GameEntity>> BrickManager::getEntityList()
	{
		return m_CurrentBricks;
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