#pragma once
#include <GameEngine.h>
#include "../Data/TagEnum.h"
namespace BreakoutGame
{
	class BreakoutObject
	{
	public:
		virtual void Start() = 0;
		virtual void Tick(float deltaTime) = 0;
		virtual std::shared_ptr<SpriteEntity> getEntity() = 0;  //TODO shouldnt be virtual
	protected:
		std::shared_ptr<SpriteEntity> m_Entity;
	};
}
