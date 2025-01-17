#include "ModelData.h"

namespace GameEngine
{
	ModelData::ModelData()
	{
	}
	ModelData::~ModelData()
	{
		ClearModel();
	}
	void ModelData::LoadModel(const std::string& fileName)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);

		if (!scene)
		{
			printf("Model (%s) failed to load: %s", fileName, importer.GetErrorString());
			return;
		}

		loadNode(scene->mRootNode, scene);

		loadMaterials(scene);
	}
	void ModelData::ClearModel()
	{
		for (size_t i = 0; i < meshList.size(); i++)
		{
			if (meshList[i])
			{
				delete meshList[i];
				meshList[i] = nullptr;
			}
		}
		for (size_t i = 0; i < textureList.size(); i++)
		{
			if (textureList[i])
			{
				delete textureList[i];
				textureList[i] = nullptr;
			}
		}
	}
	void ModelData::loadNode(aiNode* node, const aiScene* scene)
	{
		for (size_t i = 0; i < node->mNumMeshes; i++)
		{
			//node->mMeshes[i] holds the ID of mesh at node
			loadMesh(scene->mMeshes[node->mMeshes[i]], scene);
		}

		for (size_t i = 0; i < node->mNumChildren; i++)
		{
			loadNode(node->mChildren[i], scene);
		}
	}
	void ModelData::loadMesh(aiMesh* mesh, const aiScene* scene)
	{
		std::vector<GLfloat> vertices;
		std::vector<unsigned int> indices;

		for (size_t i = 0; i < mesh->mNumVertices; i++)
		{
			vertices.insert(vertices.end(), { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z });
			if (mesh->mTextureCoords[0]) //does mesh have texture coords
			{
				vertices.insert(vertices.end(), { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y });
			}
			else
			{
				vertices.insert(vertices.end(), { 0.0f, 0.0f });
			}
			//we set the aiProcess_GenSmoothNormals so normals will always exist
			vertices.insert(vertices.end(), { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z });
		}

		for (size_t i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (size_t j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}

		MeshData* newMesh = new MeshData();
		newMesh->CreateMesh(&vertices[0], &indices[0], vertices.size(), indices.size());
		meshList.push_back(newMesh);
		meshToTexList.push_back(mesh->mMaterialIndex);
	}
	void ModelData::loadMaterials(const aiScene* scene)
	{
		textureList.resize(scene->mNumMaterials);

		for (size_t i = 0; i < scene->mNumMaterials; i++)
		{
			aiMaterial* material = scene->mMaterials[i];

			textureList[i] = nullptr;

			if (material->GetTextureCount(aiTextureType_DIFFUSE))
			{
				aiString path;
				if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
				{
					int index = std::string(path.data).rfind("\\"); //or \ ?
					std::string fileName = std::string(path.data).substr(index + 1);

					std::string texPath = std::string("src/DemoScene3D/Textures/") + fileName;

					textureList[i] = new Texture(texPath.c_str());

					if (!textureList[i]->LoadTexture())
					{
						printf("Failed to load texture at %s\n", texPath);
						delete textureList[i];
						textureList[i] = nullptr;
					}
				}
			}

			if (!textureList[i])
			{
				textureList[i] = new Texture("src/DemoScene3D/Textures/plain.png");
				textureList[i]->LoadTextureWithAlpha();
			}
		}
	}
}
