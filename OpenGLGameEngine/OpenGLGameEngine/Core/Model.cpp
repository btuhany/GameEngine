#include "Model.h"

Model::Model()
{
}

void Model::LoadModel(const std::string& fileName)
{
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);

	if (!scene)
	{
		printf("Model (%s) failed to load: %s", fileName, importer.GetErrorString());
		return;
	}

	loadNode(scene->mRootNode, scene);

	loadMaterials(scene);

}

void Model::RenderModel()
{
	for (size_t i = 0; i < m_MeshList.size(); i++)
	{
		unsigned int materialIndex = m_MeshToTex[i];

		if (materialIndex < m_TextureList.size() && m_TextureList[materialIndex])
		{
			m_TextureList[materialIndex]->UseTexture();
		}

		m_MeshList[i]->RenderMesh();
	}
}

void Model::ClearModel()
{
	for (size_t i = 0; i < m_MeshList.size(); i++)
	{
		if (m_MeshList[i])
		{
			delete m_MeshList[i];
			m_MeshList[i] = nullptr;
		}
	}
	for (size_t i = 0; i < m_TextureList.size(); i++)
	{
		if (m_TextureList[i])
		{
			delete m_TextureList[i];
			m_TextureList[i] = nullptr;
		}
	}
}

Model::~Model()
{
}

void Model::loadNode(aiNode* node, const aiScene* scene)
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

void Model::loadMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<GLfloat> vertices;
	std::vector<unsigned int> indices;

	for (size_t i = 0; i < mesh->mNumVertices; i++)
	{
		vertices.insert(vertices.end(), { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z });
		if (mesh->mTextureCoords[0]) //does mesh have texture coords
		{
			vertices.insert(vertices.end(), { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y});
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

	Mesh* newMesh = new Mesh();
	newMesh->CreateMesh(&vertices[0], &indices[0], vertices.size(), indices.size());
	m_MeshList.push_back(newMesh);
	m_MeshToTex.push_back(mesh->mMaterialIndex);
}

void Model::loadMaterials(const aiScene* scene)
{
	m_TextureList.resize(scene->mNumMaterials);
	
	for (size_t i = 0; i < scene->mNumMaterials; i++)
	{
		aiMaterial* material = scene->mMaterials[i];

		m_TextureList[i] = nullptr;

		if (material->GetTextureCount(aiTextureType_DIFFUSE))
		{
			aiString path;
			if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
			{
				int index = std::string(path.data).rfind("\\"); //or \ ?
				std::string fileName = std::string(path.data).substr(index + 1);

				std::string texPath = std::string("Textures/") + fileName;

				m_TextureList[i] = new Texture(texPath.c_str());

				if (!m_TextureList[i]->LoadTexture())
				{
					printf("Failed to load texture at %s\n", texPath);
					delete m_TextureList[i];
					m_TextureList[i] = nullptr;
				}
			}
		}

		if (!m_TextureList[i])
		{
			m_TextureList[i] = new Texture("Textures/plain.png");
			m_TextureList[i]->LoadTextureWithAlpha();
		}
	}


}
