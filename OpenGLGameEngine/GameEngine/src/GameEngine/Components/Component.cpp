#include "Component.h"
namespace GameEngine
{
	void Component::AssignToEntity(GameEntity* entity)
	{
		ownerEntity = entity;
	}
}