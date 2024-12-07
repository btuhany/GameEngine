#pragma once
#include "BreakoutObject.h"
#include "IMovable.h"
namespace BreakoutGame
{
	class Paddle : public BreakoutObject, public IMovable
	{
	public:
		void Initialize(std::shared_ptr<Shader> shader) override;
		void Start() override;
		void Tick(float deltaTime) override;
		std::shared_ptr<SpriteEntity> getEntity() override;
		void MoveLeft() override;
		void MoveRight() override;
		void MoveUp() override;
		void MoveDown() override;
	private:
		float m_Speed;
		float m_DeltaTime;
	};
}

