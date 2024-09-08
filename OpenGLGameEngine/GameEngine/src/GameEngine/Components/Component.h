#pragma once
#include <memory>
#include "Core.h"

namespace GameEngine
{
	class Entity; //Forward decleration for circular dependency

	class ENGINE_API Component
	{
public:
		void AssignToEntity(Entity* entity);
		//TODOby
	protected:
		Entity* ownerEntity;
	};
}
