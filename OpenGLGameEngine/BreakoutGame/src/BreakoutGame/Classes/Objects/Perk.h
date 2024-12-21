#pragma once
#include <GameEngine.h>
#include "BreakoutObject.h"
#include "IMovable.h"
#include "../Data/PerkTypeEnum.h"
namespace BreakoutGame
{
	class Perk : public BreakoutObject
	{
	public:
		void CreateEntity(std::shared_ptr<Shader> shader);
		void UpdateData(PerkType perkType, std::shared_ptr<SpriteRenderData> spriteRenderData);
		void Start() override;
		void Tick(float deltaTime) override;
		std::shared_ptr<SpriteEntity> getEntity() override;
		PerkType getType();
		void MoveDown(float deltaTime);
	private:
		void onCollisionEnter(std::shared_ptr<CollisionData> collisionData);
		PerkType m_Type;
		const float SPEED = 2.0f;
	};
}

