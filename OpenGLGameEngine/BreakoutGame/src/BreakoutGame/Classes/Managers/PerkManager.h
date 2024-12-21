#pragma once
#include "../Data/PerkTypeEnum.h"
#include "../Data/PerkData.h"
#include "../Objects/Perk.h"
#include "../Data/BallHitBrickData.h"
#include "../Data/BrickData.h"
namespace BreakoutGame
{
	class PerkManager
	{
	public:
		void Initialize(std::shared_ptr<Shader> shader);
		void Start();
		void Tick(float deltaTime);
		std::vector<std::shared_ptr<GameEntity>> getEntityList();
		void HandleOnBallHitBrick(BallHitBrickData hitData, BrickData brickData);
		void HandleOnLevelInit();
	private:
		void spawnPerk(Vector3 pos);
		void initializePerkSpriteRenderDataMap(std::shared_ptr<Shader> shader);
		void loadSpriteIncreaseLiveToMap(std::shared_ptr<Shader> shader);
		void poolPerks(std::shared_ptr<Shader> shader);
		std::unordered_map<PerkType, std::shared_ptr<SpriteRenderData>> m_PerkSpriteRenderDataMap;
		std::vector<std::shared_ptr<Perk>> m_PerkPool;
		const int MAX_PERK_COUNT_INGAME = 1;
	};
}

