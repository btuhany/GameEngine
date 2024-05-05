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
	void Draw(glm::mat4 modelMatrix, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, Camera* mainCamera, RenderableData* renderData);
	~Renderer();
protected:
	virtual void RenderData(RenderableData* renderData);
private:
	Material* m_Material;
	Shader* m_Shader;
};

