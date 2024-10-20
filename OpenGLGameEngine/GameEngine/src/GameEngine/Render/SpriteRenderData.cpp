#include "SpriteRenderData.h"
namespace GameEngine
{
	SpriteRenderData::SpriteRenderData(std::shared_ptr<Texture> textureData, std::shared_ptr<Material> materialData, std::shared_ptr<Shader> shaderData) : RenderData(textureData, materialData, shaderData)
	{
	}
	void SpriteRenderData::createQuadMesh()
	{
  //      float vertices[] = {
  //          // pos      // tex
  //          0.0f, 1.0f, 0.0f, 1.0f,
  //          1.0f, 0.0f, 1.0f, 0.0f,
  //          0.0f, 0.0f, 0.0f, 0.0f,

  //          0.0f, 1.0f, 0.0f, 1.0f,
  //          1.0f, 1.0f, 1.0f, 1.0f,
  //          1.0f, 0.0f, 1.0f, 0.0f
  //      };

		//GLfloat vertices[] =
		//{
		//	//x      y     z		 u     y			normals
		//	-1.0f, -1.0f, 0.0f, 	0.0f, 0.0f,		0.0f, 0.0f, 1.0f,
		//	1.0f, -1.0f, 0.0f,	1.0f, 0.0f,		0.0f, 0.0f, 1.0f,
		//	1.0f, 1.0f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, 1.0f,
		//	-1.0f, 1.0f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 1.0f
		//};

		//unsigned int indices[] = {
		//2, 0, 3,
		//1, 0, 2,
		//};

		//std::shared_ptr<MeshData> cubeMesh = std::make_shared<MeshData>();
		//cubeMesh->CreateMesh(vertices, indices, 64, 36);
		//return cubeMesh;

	}
}
