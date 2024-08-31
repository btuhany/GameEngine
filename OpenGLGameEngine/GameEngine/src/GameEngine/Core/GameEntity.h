#pragma once
#include "Entity.h"
#include "Components/Transform.h"
namespace GameEngine
{
	class ENGINE_API GameEntity : public Entity
	{	
	public:
		GameEntity();
		~GameEntity();
		std::shared_ptr<Transform> transform;
	};
}

