#include "IEntityProvider.h"
namespace BreakoutGame
{
	std::vector<std::shared_ptr<GameEntity>> IEntityProvider::getEntityList()
	{
		return std::vector<std::shared_ptr<GameEntity>>();
	}
}