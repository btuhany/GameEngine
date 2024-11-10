#pragma once
#include <memory>
#include "../Core.h"
#include "../Debugging/Log.h"

namespace GameEngine
{
	enum class ComponentType
	{
		None = 0,
		MeshRenderer = 1,
		ModelRenderer = 2,
		Renderer = 3,
		Transform = 4,
		Collision = 5
	};

	class GameEntity; //Forward decleration for circular dependency

	class ENGINE_API Component
	{
	public:
		void AssignToEntity(std::shared_ptr<GameEntity> entity);
		virtual void HandleOnPreOwnerDestroyed();
		virtual void HandleOnAfterOwnerInstantiated();
		virtual void HandleOnOwnerSetActive(bool isActive);
		std::weak_ptr<GameEntity> getEntity();
		void setEnabled(bool isEnable);
		bool getEnabled();
		virtual ComponentType getType() = 0;
	protected:
		std::weak_ptr<GameEntity> m_OwnerEntity;
	private:
		bool m_IsEnabled = false;
	};
}

