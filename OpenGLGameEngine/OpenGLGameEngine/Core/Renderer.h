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
	void DrawData(GLuint uniformModel, glm::mat4 modelMatrix, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, Camera* mainCamera, RenderableData* renderData);
	void RenderObjectWithShader(glm::mat4 modelMatrix, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, Camera* mainCamera, RenderableData* renderData, DirectionalLight* directionalLight);
	~Renderer();
private:
	Material* m_Material;
	Shader* m_Shader;
	GLuint m_UniformModel;
	GLuint m_UniformProjection;
	GLuint m_UniformView;
	GLuint m_UniformMatSpecularInstensity;
	GLuint m_UniformMatShininess;
	GLuint m_UniformCameraPosition;
};

