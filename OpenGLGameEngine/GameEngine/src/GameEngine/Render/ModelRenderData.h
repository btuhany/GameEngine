#pragma once
#include "../Core.h"
#include "../Resource/ModelData.h"
#include "../Resource/Texture.h"
#include "../Resource/Material.h"
#include "../Resource/Shader.h"
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

