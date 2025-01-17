#pragma once
#include <GameEngine.h>
#include "IEntityProvider.h"
#include "../Data/BrickProperties.h"
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
		void Tick(float deltaTime);
		void UpdateBrickGrid(BrickGridData brickTypeGridData);
		void PlayBrickGridEnterAnimation(std::function<void()> onAnimationEndCallback);
		std::vector<std::shared_ptr<GameEntity>> getEntityList();
		BallHitBrickData HandleOnGotHitByBall(std::shared_ptr<GameEntity> brickEntity);
		std::shared_ptr<BrickProperties> GetBrickData(BrickType brickType);
		void HideAllBricks();
	private:
		void tickActiveBricksEnterAnimation(float animationLerpValue);
		void finalizeActiveBricksEnterAnimation();
		BallHitBrickData processBrick(std::shared_ptr<Brick> brick);
		void initializeEasyBrickData(std::shared_ptr<Shader> shader);
		void initializeMediumBrickData(std::shared_ptr<Shader> shader);
		void initializeHardBrickData(std::shared_ptr<Shader> shader);
		std::shared_ptr<Brick> findBrick(std::shared_ptr<GameEntity> brickEntity);
		std::vector<std::vector<std::shared_ptr<Brick>>> m_BrickGrid;
		const Vector2 SPACING = Vector2(7.0f, 3.0f);
		const Vector2 START_POS = Vector2(-35.0f, 18.0f);

		//TODO: fixing brick data also contains brick type 
		std::unordered_map<BrickType, std::shared_ptr<BrickProperties>> m_BrickDataMap;

		float m_AnimationLerpValue;
		bool m_IsEnterAnimationPlaying;
		std::function<void()> m_OnEnterAnimationEnd;

		int m_ActiveBrickCount;
		std::function<void()> m_OnThereIsNoActiveBricksLeft;

		const float ENTER_ANIMATION_OFFSET_X = 40.0f;
	};
}

