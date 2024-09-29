#include "GameEntity.h"

namespace GameEngine
{
    GameEntity::GameEntity()
    {
		transform = std::make_shared<Transform>();
		AddComponent<Transform>(transform);
    }
}