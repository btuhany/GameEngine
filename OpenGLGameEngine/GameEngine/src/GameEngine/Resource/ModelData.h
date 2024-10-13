#pragma once
#include "../Core.h"
#include "MeshData.h"
#include "Texture.h"
#include <string>
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
namespace GameEngine
{
	class ENGINE_API ModelData
	{
	public:
		ModelData();
		void LoadModel(const std::string& fileName);
		//void Render() override;
		void ClearModel();
		std::vector<MeshData*> m_MeshList;
		std::vector<Texture*> m_TextureList;
		std::vector<unsigned int> m_MeshToTex;
	private:
		void loadNode(aiNode* node, const aiScene* scene);
		void loadMesh(aiMesh* mesh, const aiScene* scene);
		void loadMaterials(const aiScene* scene);
	};
}

