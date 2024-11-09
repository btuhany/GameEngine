#pragma once
#include <GameEngine.h>
namespace BreakoutGame
{
	class BreakoutObject
	{
	public:
		virtual void Initialize(std::shared_ptr<Shader> shader) = 0;
		virtual void Start() = 0;
		virtual void Tick(float deltaTime) = 0;
		virtual void MoveLeft() = 0;
		virtual void MoveRight() = 0;
		virtual void MoveUp() = 0;
		virtual void MoveDown() = 0;
		virtual std::shared_ptr<SpriteEntity> getEntity() = 0;
	};
}
