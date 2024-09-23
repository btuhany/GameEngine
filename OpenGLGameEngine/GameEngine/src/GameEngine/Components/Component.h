#pragma once
#include <memory>
#include "../Core.h"

namespace GameEngine
{
	enum class ComponentType
	{
		None = 0,
		MeshRenderer = 1,
		ModelRenderer,
		SpriteRenderer
	};

	class Entity; //Forward decleration for circular dependency

	class ENGINE_API Component
	{
	public:
		void AssignToEntity(Entity* entity);
	protected:
		Entity* ownerEntity;  //TODO weak pointer
	};
}

