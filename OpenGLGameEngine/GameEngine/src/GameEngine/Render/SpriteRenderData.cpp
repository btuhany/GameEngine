#include "SpriteRenderData.h"
namespace GameEngine
{
	SpriteRenderData::SpriteRenderData(std::shared_ptr<Texture> textureData, std::shared_ptr<Material> materialData, std::shared_ptr<Shader> shaderData) : RenderData(textureData, materialData, shaderData)
	{
		quadMesh = createQuadMesh();
	}
	std::shared_ptr<MeshData> SpriteRenderData::createQuadMesh()
	{
		GLfloat vertices[] =
		{
			//x      y     z		 u     y			normals
			-1.0f, -1.0f, 0.0f, 	0.0f, 1.0f,		0.0f, 0.0f, 1.0f,
			1.0f, -1.0f, 0.0f,	1.0f, 1.0f,		0.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 1.0f,
			-1.0f, 1.0f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 1.0f
		};

		unsigned int indices[] = {
			0,1,2,
			2,3,0
		};

		std::shared_ptr<MeshData> cubeMesh = std::make_shared<MeshData>();
		cubeMesh->CreateMesh(vertices, indices, 32, 6);
		return cubeMesh;
	}
}
