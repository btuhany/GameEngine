#pragma once
#include "Material.h"
#include "Mesh.h"
#include "Texture.h"
#include "Model.h"
#include "Shader.h"
#include "Camera.h"

class Renderer
{
public:
	Renderer();
	~Renderer();
	Renderer(Model* model, Material* material, Shader* shader);
	Renderer(Mesh* mesh, Texture* texture, Material* material, Shader* shader);
	void RenderUpdate(glm::mat4 modelMatrix, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, Camera* mainCamera);
private:
	Material* m_Material;
	Mesh* m_Mesh;
	Texture* m_Texture;
	Model* m_Model;
	Shader* m_Shader;
};

