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
	void Component::setEnabled(bool isEnable)
	{
		m_IsEnabled = isEnable;
	}
	bool Component::getEnabled()
	{
		return m_IsEnabled;
	}
}