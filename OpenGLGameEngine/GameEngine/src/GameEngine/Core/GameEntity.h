#pragma once
#include "Entity.h"
#include "Components/Transform.h"
namespace GameEngine
{
	class GameEntity : public Entity
	{	
	public:
		Transform TransformComponent;
	};
}

