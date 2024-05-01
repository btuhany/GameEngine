#pragma once
#include "Material.h"
#include "Mesh.h"
#include "Texture.h"
#include "Model.h"
#include "Shader.h"
#include "Camera.h"
#include "RenderableData.h"

class Renderer
{
public:
	Renderer();
	Renderer(Material* material, Shader* shader);
	void Initialize(RenderableData* renderableData);
	void Draw(glm::mat4 modelMatrix, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, Camera* mainCamera);	
	~Renderer();
protected:
	virtual void RenderData();
private:
	Material* m_Material;
	Shader* m_Shader;
	RenderableData* m_RenderableData;
};

