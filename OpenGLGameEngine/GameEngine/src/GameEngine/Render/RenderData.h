#pragma once
#include <memory>
#include <stdio.h>
#include "../Core.h"
#include "../Resource/MeshData.h"
#include "../Resource/Texture.h"
#include "../Resource/Material.h"
#include "../Resource/Shader.h"

namespace GameEngine
{
	class ENGINE_API RenderData
	{
	public:
		RenderData(std::shared_ptr<Texture> textureData, std::shared_ptr<Material> materialData,
			std::shared_ptr<Shader> shaderData);
		std::shared_ptr<Texture> texture;
		std::shared_ptr<Material> material;
		std::shared_ptr<Shader> shader;
	};
}

