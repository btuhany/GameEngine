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
		void Initialize(std::shared_ptr<Shader> shader, std::function<void(PerkType)> onPerkGainedCallback);
		void Start();
		void Tick(float deltaTime);
		std::vector<std::shared_ptr<GameEntity>> getEntityList();
		void HandleOnBallHitBrick(BallHitBrickData hitData, BrickData brickData);
		void HandleOnLevelInit();
		void HidePerks();
		const float PADDLE_SCALE_CHANGE_VALUE = 0.7f;
		const float PADDLE_SPEED_CHANGE_VALUE = 10.0f;
	private:
		std::function<void(PerkType)> m_OnPerkGainedHandler;
		std::shared_ptr<Perk> findPerk(std::shared_ptr<GameEntity> entity);
		void onPerkCollideWithPaddle(std::shared_ptr<GameEntity> entity);
		float getPerkProbability(PerkType perkType, float multiplier);
		void trySpawnPerk(Vector3 pos);
		void initializePerkSpriteRenderDataMap(std::shared_ptr<Shader> shader);
		void poolPerks(std::shared_ptr<Shader> shader);
		std::unordered_map<PerkType, std::shared_ptr<SpriteRenderData>> m_PerkSpriteRenderDataMap;
		std::vector<std::shared_ptr<Perk>> m_PerkPool;
		
		PerkType getRandomPerkType();
		void initCumulativePerkTypeProbabilities();
		void printProbabilities(); //FOR DEBUG
		std::vector<float> m_CumulativePerkTypeProbabilityList;
		const int MAX_PERK_COUNT_INGAME = 5;
		const std::unordered_map<PerkType, float> m_PerkProbabilityMap = {
			{ PerkType::IncreaseLive, 0.0f },
			{ PerkType::DecreaseLive, 0.0f },
			{ PerkType::ThreeBall, 0.0f },
			{ PerkType::PaddleScaleUp, 0.0f },
			{ PerkType::PaddleScaleDown, 0.0f },
			{ PerkType::PaddleSpeedUp, 0.5f },
			{ PerkType::PaddleSpeedDown, 0.5f },
		};
		const std::array<PerkType, 7> m_AllPerkTypeArr = {
			PerkType::IncreaseLive,
			PerkType::DecreaseLive,
			PerkType::ThreeBall,
			PerkType::PaddleScaleUp,
			PerkType::PaddleScaleDown,
			PerkType::PaddleSpeedUp,
			PerkType::PaddleSpeedDown,
		};
	};
}

