#pragma once
#include <memory>
#include "../Core.h"
#include "../Resource/Shader.h"
#include "../Resource/MeshData.h"
namespace GameEngine
{
	class ENGINE_API UIRenderData
	{
	public:
		UIRenderData(std::shared_ptr<Shader> shaderData);
		std::shared_ptr<Shader> shader;
		GLuint VAO, VBO, IBO;
	private:
		void createQuad();
	};
}

