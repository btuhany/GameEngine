#pragma once
#include <memory>
#include <string>
#include <GameEngine.h>
#include "../Data/BrickProperties.h"
#include "../Data/TagEnum.h"
#include "../Data/BrickTypeEnum.h"
#include "BreakoutObject.h"

namespace BreakoutGame
{
	class Brick
	{
	public:
		void Initialize(std::string entityName, std::shared_ptr<BrickProperties> properties);
		void ResetUpdateData(std::shared_ptr<BrickProperties> properties);
		void UpdateSprite(std::shared_ptr<SpriteRenderData> spriteRenderData);
		void SetPosition(Vector2 pos);
		void HandleOnBallHit();
		std::shared_ptr<SpriteEntity> getEntity();
		BrickType getType();
		void ResetHitCount();

		void TickAnimation(float lerpValue);
		void InitializeEnterAnimStart(Vector3 startPos);
		void StopAnimationResetPos();
		int hitCount;
	private:
		Vector3 m_EnterAnimStartPosition;
		Vector3 m_EnterAnimStopPosition;
		std::shared_ptr<SpriteEntity> m_Entity;
		BrickType m_Type;
	};
}

