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
		void Initialize(std::shared_ptr<SpriteEntity> brickEntity, std::shared_ptr<BrickData> data);
		void HandleOnBallHit();
		std::shared_ptr<SpriteEntity> getEntity();
		std::shared_ptr<BrickData> getData();
		void Reset();

		int hitCount;
	private:
		std::shared_ptr<SpriteEntity> m_Entity;
		std::shared_ptr<BrickData> m_Data;
	};
}

