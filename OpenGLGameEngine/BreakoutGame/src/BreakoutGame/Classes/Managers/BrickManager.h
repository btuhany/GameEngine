#pragma once
#include <GameEngine.h>
#include "IEntityProvider.h"
#include "../Data/BrickData.h"
#include "../Objects/Brick.h"
#include "../Data/BallHitBrickData.h"
#include "../Data/BrickGridData.h"
#include "../Data/LevelDataCommon.h"
namespace BreakoutGame
{
	class BrickManager : public IEntityProvider
	{
	public:
		void Initialize(std::shared_ptr<Shader> mainShader, std::function<void()> onThereIsNoActiveBricksLeftHandler);
		void PoolBricks();
		void HandleOnAfterBricksInstantiated();
		void Reset();
		void UpdateBrickGrid(BrickGridData brickTypeGridData);
		std::vector<std::shared_ptr<GameEntity>> getEntityList();
		BallHitBrickData HandleOnGotHitByBall(std::shared_ptr<GameEntity> brickEntity);
		std::shared_ptr<BrickData> GetBrickData(BrickType brickType);
	private:
		BallHitBrickData processBrick(std::shared_ptr<Brick> brick);
		void initializeEasyBrickData(std::shared_ptr<Shader> shader);
		void initializeMediumBrickData(std::shared_ptr<Shader> shader);
		void initializeHardBrickData(std::shared_ptr<Shader> shader);

		std::shared_ptr<Brick> findBrick(std::shared_ptr<GameEntity> brickEntity);
		std::vector<std::vector<std::shared_ptr<Brick>>> m_BrickGrid;
		const Vector2 SPACING = Vector2(7.0f, 3.0f);
		const Vector2 START_POS = Vector2(-35.0f, 18.0f);

		std::unordered_map<BrickType, std::shared_ptr<BrickData>> m_BrickDataMap;


		int m_ActiveBrickCount;
		std::function<void()> m_OnThereIsNoActiveBricksLeft;
	};
}

