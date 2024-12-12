#include "BrickManager.h"
namespace BreakoutGame
{
	void BrickManager::Initialize(std::shared_ptr<Shader> mainShader)
	{
		std::shared_ptr<Texture> blueTex = std::make_shared<Texture>("src/BreakoutGame/Textures/01-Breakout-Tiles.PNG");
		blueTex->LoadTextureWithAlpha();
		std::shared_ptr<Texture> purpleTex = std::make_shared<Texture>("src/BreakoutGame/Textures/05-Breakout-Tiles.PNG");
		purpleTex->LoadTextureWithAlpha();

		std::shared_ptr<SpriteRenderData> breakoutSpriteRenderData = std::make_shared<SpriteRenderData>(blueTex, nullptr, mainShader);


		float radius = 12.0f;
		float angleIncrement = 2 * glm::pi<float>() / 10;

		for (size_t i = 0; i < 10; i++)
		{
			std::shared_ptr<SpriteEntity> spriteEntity = std::make_shared<SpriteEntity>(breakoutSpriteRenderData);
			std::string name = std::to_string(i) + ".Tile";
			spriteEntity->setName(name);

			float angle = i * angleIncrement;
			float x = radius * glm::cos(angle);
			float y = radius * glm::sin(angle);

			spriteEntity->transform->SetPosition(glm::vec3(x, y, 0.0f));
			auto boxCollider2DComp = std::make_shared<BoxCollider2DComponent>(6.0f, 2.0f, CollisionType::Static);
			spriteEntity->AddComponent<BoxCollider2DComponent>(boxCollider2DComp);
			m_CurrentBricks.push_back(spriteEntity);
		}

		for (size_t i = 0; i < 8; i++)
		{
			std::shared_ptr<SpriteEntity> spriteEntity = std::make_shared<SpriteEntity>(breakoutSpriteRenderData);
			std::string name = std::to_string(i) + ".Tile";
			spriteEntity->setName(name);

			float angle = i * angleIncrement;
			float x = 2.0f * radius * glm::cos(angle);
			float y = 2.0f * radius * glm::sin(angle);

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
}