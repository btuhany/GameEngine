#pragma once
#include <GameEngine.h>
namespace BreakoutGame
{
	class IEntityProvider
	{
	public:
		virtual std::vector<std::shared_ptr<GameEntity>> getEntityList() = 0;
	};
}

