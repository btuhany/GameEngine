#pragma once
#include "BreakoutObject.h"
#include "IMovable.h"
#include "../Data/PerkTypeEnum.h"
namespace BreakoutGame
{
	class Perk : public BreakoutObject, public IMovable
	{
	public:
		void CreateEntity(std::shared_ptr<Shader> shader);
		void UpdateData(PerkType perkType, std::shared_ptr<SpriteRenderData> spriteRenderData);
		void Start() override;
		void Tick(float deltaTime) override;
		std::shared_ptr<SpriteEntity> getEntity() override;

		PerkType getType();
		void MoveLeft() override;
		void MoveRight() override;
		void MoveUp() override;
		void MoveDown() override;
	private:
		PerkType m_Type;
	};
}

