#pragma once
#include <memory>
#include "../Core.h"

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

	class Entity; //Forward decleration for circular dependency

	class ENGINE_API Component
	{
	public:
		void AssignToEntity(Entity* entity);
		virtual ComponentType GetType() = 0;
	protected:
		Entity* ownerEntity;  //TODO weak pointer
	};
}

