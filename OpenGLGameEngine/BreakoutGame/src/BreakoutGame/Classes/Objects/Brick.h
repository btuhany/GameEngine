#pragma once
#include <memory>
#include <GameEngine.h>
#include "../Data/BrickData.h"
#include "BreakoutObject.h"

namespace BreakoutGame
{
	class Brick
	{
	public:
		void Initialize(std::shared_ptr<SpriteEntity> brickEntity, std::shared_ptr<SpriteRenderData> initialRenderData, BrickType type);
		void UpdateSprite(std::shared_ptr<SpriteRenderData> spriteRenderData);
		void UpdateType(BrickType brickType);

		void HandleOnBallHit();
		std::shared_ptr<SpriteEntity> getEntity();
		BrickType getType();
		void ResetHitCount();

		int hitCount;
	private:
		std::shared_ptr<SpriteEntity> m_Entity;
		BrickType m_Type;
	};
}

