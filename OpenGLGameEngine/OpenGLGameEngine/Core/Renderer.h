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
	Renderer(Material* material, Shader* shader, Shader* dirShadowShader);
	void DrawData(GLuint uniformModel, glm::mat4 modelMatrix, RenderableData* renderData);
	void RenderObjectWithShader(glm::mat4 modelMatrix, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, Camera* mainCamera, RenderableData* renderData, DirectionalLight* directionalLight);
	void RenderObjectForDirectionalShadow(glm::mat4 modelMatrix, DirectionalLight* directionalLight, RenderableData* renderData);
	~Renderer();
private:
	Material* m_Material;
	Shader* m_Shader;
	Shader* m_DirShadowShader;
	GLuint m_UniformModel;
	GLuint m_UniformProjection;
	GLuint m_UniformView;
	GLuint m_UniformMatSpecularInstensity;
	GLuint m_UniformMatShininess;
	GLuint m_UniformCameraPosition;
	glm::mat4 m_LightTransform;
};

