#include "BrickManager.h"
namespace BreakoutGame
{
	void BrickManager::Initialize(std::shared_ptr<Shader> mainShader)
	{
		initializeEasyBrickData();
		initializeMediumBrickData();
		initializeHardBrickData();


		std::shared_ptr<SpriteRenderData> breakoutSpriteRenderData = std::make_shared<SpriteRenderData>(blueTex, nullptr, mainShader);


		for (size_t i = 0; i < 10; i++)
		{
			std::shared_ptr<SpriteEntity> spriteEntity = std::make_shared<SpriteEntity>(breakoutSpriteRenderData);
			std::string name = std::to_string(i) + ".Tile";
			spriteEntity->setName(name);


			spriteEntity->transform->SetPosition(glm::vec3(x, y, 0.0f));
			auto boxCollider2DComp = std::make_shared<BoxCollider2DComponent>(6.0f, 2.0f, CollisionType::Static);
			spriteEntity->AddComponent<BoxCollider2DComponent>(boxCollider2DComp);
			m_CurrentBricks.push_back(spriteEntity);
		}
	}
	std::vector<std::shared_ptr<GameEntity>> BrickManager::getEntityList()
	{
		return m_CurrentBricks;
	}
	void BrickManager::initializeEasyBrickData()
	{
		m_EasyBrickData = std::make_shared<BrickData>();
		m_EasyBrickData->hitCountToBreak = 1;
		m_EasyBrickData->scorePointOnHit = 0;
		m_EasyBrickData->scorePointOnBreak = 10;
		m_EasyBrickData->isAbleToDropHealthPoint = false;
		m_EasyBrickData->isAbleToDropPerk = false;
		m_EasyBrickData->isAbleToDropExtraScorePoint = false;

		std::shared_ptr<Texture> easyBrickTexture = std::make_shared<Texture>("src/BreakoutGame/Textures/03-Breakout-Tiles.PNG");
		m_EasyBrickData->textureListOrderedByHitCountAscending.push_back(easyBrickTexture);
	}
	void BrickManager::initializeMediumBrickData()
	{
		m_MediumBrickData = std::make_shared<BrickData>();
		m_MediumBrickData->hitCountToBreak = 2;
		m_MediumBrickData->scorePointOnHit = 5;
		m_MediumBrickData->scorePointOnBreak = 10;
		m_MediumBrickData->isAbleToDropHealthPoint = false;
		m_MediumBrickData->isAbleToDropPerk = false;
		m_MediumBrickData->isAbleToDropExtraScorePoint = false;

		std::shared_ptr<Texture> mediumBrickTexture = std::make_shared<Texture>("src/BreakoutGame/Textures/05-Breakout-Tiles.PNG");
		std::shared_ptr<Texture> mediumBrokenBrickTexture = std::make_shared<Texture>("src/BreakoutGame/Textures/06-Breakout-Tiles.PNG");
		m_MediumBrickData->textureListOrderedByHitCountAscending.push_back(mediumBrickTexture);
		m_MediumBrickData->textureListOrderedByHitCountAscending.push_back(mediumBrokenBrickTexture);
	}
	void BrickManager::initializeHardBrickData()
	{
		m_HardBrickData = std::make_shared<BrickData>();
		m_HardBrickData->hitCountToBreak = 3;
		m_HardBrickData->scorePointOnHit = 5;
		m_HardBrickData->scorePointOnBreak = 15;
		m_HardBrickData->isAbleToDropHealthPoint = false;
		m_HardBrickData->isAbleToDropPerk = false;
		m_HardBrickData->isAbleToDropExtraScorePoint = false;

		std::shared_ptr<Texture> hardBrickTexture = std::make_shared<Texture>("src/BreakoutGame/Textures/07-Breakout-Tiles.PNG");
		std::shared_ptr<Texture> hardBrokenBrickTexture = std::make_shared<Texture>("src/BreakoutGame/Textures/08-Breakout-Tiles.PNG");
		std::shared_ptr<Texture> hardBroken2BrickTexture = std::make_shared<Texture>("src/BreakoutGame/Textures/081-Breakout-Tiles.PNG");
		m_HardBrickData->textureListOrderedByHitCountAscending.push_back(hardBrickTexture);
		m_HardBrickData->textureListOrderedByHitCountAscending.push_back(hardBrokenBrickTexture);
		m_HardBrickData->textureListOrderedByHitCountAscending.push_back(hardBroken2BrickTexture);
	}
}