#include "Renderer.h"


Renderer::Renderer()
{
}

Renderer::~Renderer()
{

}

Renderer::Renderer(Material* material, Shader* shader)
{
	m_Material = material;
	m_Shader = shader;
}

void Renderer::Draw(glm::mat4 modelMatrix, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, Camera* mainCamera, RenderableData* renderData)
{
	GLuint uniformModel = m_Shader->GetModelLocation();
	GLuint uniformProjection = m_Shader->GetProjectionLocation();
	GLuint uniformView = m_Shader->GetViewLocation();
	GLuint uniformMatSpecularInstensity = m_Shader->GetMatSpecularIntensityLocation();
	GLuint uniformMatShininess = m_Shader->GetMatShininessLocation();
	GLuint uniformCameraPosition = m_Shader->GetCameraPositionLocation();

	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniform3f(uniformCameraPosition, mainCamera->GetCameraPosition().x, mainCamera->GetCameraPosition().y, mainCamera->GetCameraPosition().z);

	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	m_Shader->SetTextureUnit(1);
	m_Shader->UseShader();

	m_Material->UseMaterial(uniformMatSpecularInstensity, uniformMatShininess);

	RenderData(renderData);
}

void Renderer::RenderData(RenderableData* renderData)
{
	renderData->TextureData->UseTexture();
	renderData->Renderable->Render();
}

