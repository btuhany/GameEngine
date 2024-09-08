#pragma once
#include <memory>
#include "Core.h"
#include "MeshData.h"
#include "Texture.h"
#include "Material.h"
#include "Shader.h"
namespace GameEngine
{
	class ENGINE_API MeshRenderData
	{
	public:
		//TODOby all pointers?
		//TODOby deconstructor
		MeshData* meshData;
		Texture* textureData;
		Material*  materialData;
		Shader*  shader;
	};
}

