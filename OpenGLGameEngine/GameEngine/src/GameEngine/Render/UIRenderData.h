#pragma once
#include <memory>
#include "../Core.h"
#include "../Resource/Shader.h"
#include "../Resource/MeshData.h"
#include "../Resource/Texture.h"
namespace GameEngine
{
	class ENGINE_API UIRenderData
	{
	public:
		UIRenderData(std::shared_ptr<Shader> shaderData);
		UIRenderData(std::shared_ptr<Shader> shaderData, std::shared_ptr<Texture> textureData);
		std::shared_ptr<Shader> shader;
		std::shared_ptr<Texture> texture;
		GLuint VAO, VBO, IBO;
	private:
		void createQuad();
	};
}

