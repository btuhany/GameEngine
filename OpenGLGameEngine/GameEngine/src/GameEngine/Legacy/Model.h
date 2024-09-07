//#pragma once
//
//namespace GameEngine {
//	class ENGINE_API Model : public IRenderable
//	{
//	public:
//		Model();
//
//		void LoadModel(const std::string& fileName);
//		void Render() override;
//		void ClearModel();
//
//		~Model();
//	private:
//		void loadNode(aiNode* node, const aiScene* scene);
//		void loadMesh(aiMesh* mesh, const aiScene* scene);
//		void loadMaterials(const aiScene* scene);
//
//		std::vector<Mesh*> m_MeshList;
//		std::vector<Texture*> m_TextureList;
//		std::vector<unsigned int> m_MeshToTex;
//	};
//}
