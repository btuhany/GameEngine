#include "Component.h"
namespace GameEngine
{
	void Component::AssignToEntity(Entity* entity)
	{
		ownerEntity = entity;
	}
}