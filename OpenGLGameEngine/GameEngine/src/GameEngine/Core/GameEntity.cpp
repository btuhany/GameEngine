#include "GameEntity.h"
#include "Log.h"
namespace GameEngine
{
	GameEntity::GameEntity()
	{
		transform = std::make_shared<Transform>();
		AddComponent<Transform>(transform);
	}

	GameEntity::~GameEntity()
	{

	}
}
