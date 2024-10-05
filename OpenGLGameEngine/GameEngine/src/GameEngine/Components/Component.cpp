#include "Component.h"
namespace GameEngine
{
	void Component::AssignToEntity(std::shared_ptr<GameEntity> entity)
	{
		ownerEntity = entity;
	}
	std::weak_ptr<GameEntity> Component::GetEntity()
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