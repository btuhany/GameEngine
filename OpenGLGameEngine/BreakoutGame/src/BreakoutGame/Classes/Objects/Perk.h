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
		void CreateEntity(std::shared_ptr<Shader> shader, std::function<void(std::shared_ptr<GameEntity>)> onPaddleCollideCallback);
		void UpdateData(PerkType perkType, std::shared_ptr<SpriteRenderData> spriteRenderData);
		void Start() override;
		void Tick(float deltaTime) override;
		std::shared_ptr<SpriteEntity> getEntity() override;
		PerkType getType();
		void MoveDown(float deltaTime);
	private:
		std::function<void(std::shared_ptr<GameEntity>)> m_OnPaddleCollideCallbackHandler;
		std::shared_ptr<BoxCollider2DComponent> m_Collider;
		void onCollisionEnter(std::shared_ptr<CollisionData> collisionData);
		PerkType m_Type;
		const float SPEED = 10.0f;
	};
}

