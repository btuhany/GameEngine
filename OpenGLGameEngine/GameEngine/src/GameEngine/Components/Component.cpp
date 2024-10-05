#include "Component.h"
namespace GameEngine
{
	void Component::AssignToEntity(std::shared_ptr<GameEntity> entity)
	{
		m_ownerEntity = entity;
	}
	std::weak_ptr<GameEntity> Component::GetEntity()
	{
		return m_ownerEntity;
	}
	void Component::setEnabled(bool isEnable)
	{
		m_isEnabled = isEnable;
	}
	bool Component::getEnabled()
	{
		return m_isEnabled;
	}
}