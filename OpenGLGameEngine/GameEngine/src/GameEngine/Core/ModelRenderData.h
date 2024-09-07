#pragma once
#include "Core.h"
#include "ModelData.h"
#include "Texture.h"
#include "Material.h"
#include "Shader.h"
#include "ModelData.h"
namespace GameEngine
{
	class ENGINE_API ModelRenderData
	{
	public:
		//TODOby all pointers?
		//TODOby deconstructor
		ModelData* modelData;
		Texture* textureData;
		Material* materialData;
		Shader* shader;
	};
}

