#pragma once
#include <memory>
#include "../Core.h"
#include "../Resource/MeshData.h"
#include "../Resource/Shader.h"

namespace GameEngine
{
	class ENGINE_API DebugRenderData
	{
	public:
		DebugRenderData(std::shared_ptr<MeshData> meshData, std::shared_ptr<Shader> shaderData);
		std::shared_ptr<MeshData> mesh;
		std::shared_ptr<Shader> shader;
	};
}

