#include "RenderData.h"

namespace GameEngine
{
	RenderData::RenderData(std::shared_ptr<Texture> textureData, std::shared_ptr<Material> materialData, std::shared_ptr<Shader> shaderData)
	{
		texture = textureData;
		material = materialData;
		shader = shaderData;
	}
}
