#include "Component.h"
namespace GameEngine
{
	void Component::AssignToEntity(std::shared_ptr<GameEntity> entity)
	{
		m_OwnerEntity = entity;
	}
	void Component::HandleOnPreOwnerDestroyed()
	{

	}
	void Component::HandleOnAfterOwnerInstantiated()
	{
	}
	void Component::HandleOnOwnerSetActive(bool isActive)
	{

	}
	std::weak_ptr<GameEntity> Component::getEntity()
	{
		return m_OwnerEntity;
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