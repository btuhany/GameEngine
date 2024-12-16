#pragma once
#include <GameEngine.h>
#include "../Data/TagEnum.h"
namespace BreakoutGame
{
	class BreakoutObject
	{
	public:
		virtual void Initialize(std::shared_ptr<Shader> shader) = 0;
		virtual void Start() = 0;
		virtual void Tick(float deltaTime) = 0;
		virtual std::shared_ptr<SpriteEntity> getEntity() = 0;
	protected:
		std::shared_ptr<SpriteEntity> m_Entity;
	};
}
