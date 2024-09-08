#pragma once
#include <memory>
#include "../Core.h"
#include "../Resource/MeshData.h"
#include "../Resource/Texture.h"
#include "../Resource/Material.h"
#include "../Resource/Shader.h"
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

