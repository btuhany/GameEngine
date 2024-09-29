#include "Component.h"
namespace GameEngine
{
	void Component::AssignToEntity(GameEntity* entity)
	{
		ownerEntity = entity;
	}
	GameEntity* Component::GetEntity()
	{
		return ownerEntity;
	}
}