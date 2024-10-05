#pragma once
#include <memory>
#include "../Core.h"
#include "../Debug/Log.h"

namespace GameEngine
{
	enum class ComponentType
	{
		None = 0,
		MeshRenderer = 1,
		ModelRenderer = 2,
		Renderer = 3,
		Transform = 4
	};

	class GameEntity; //Forward decleration for circular dependency

	class ENGINE_API Component
	{
	public:
		void AssignToEntity(std::shared_ptr<GameEntity> entity);
		std::weak_ptr<GameEntity> GetEntity();
		void setEnabled(bool isEnable);
		bool getEnabled();
		virtual ComponentType GetType() = 0;
	protected:
		std::weak_ptr<GameEntity> ownerEntity;  //TODO weak pointer
	private:
		bool m_IsEnabled = false;
	};
}

