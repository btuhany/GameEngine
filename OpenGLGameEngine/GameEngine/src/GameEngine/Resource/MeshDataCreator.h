#pragma once
#include "../Core.h"
#include "MeshData.h"
#include <memory>
namespace GameEngine
{
	class ENGINE_API MeshDataCreator
	{
	public:
		static std::shared_ptr<MeshData> CreateQuadMesh();
	};
}

