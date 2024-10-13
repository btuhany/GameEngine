#pragma once
#include "../Core.h"
#include "RenderData.h"
#include "../Resource/ModelData.h"
namespace GameEngine
{
	class ENGINE_API ModelRenderData : public RenderData
	{
	public:
		ModelRenderData(std::shared_ptr<ModelData> modelData, std::shared_ptr<Texture> textureData, std::shared_ptr<Material> materialData,
			std::shared_ptr<Shader> shaderData);
		std::shared_ptr<ModelData> model;
	};
}

