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
	m_UniformModel = m_Shader->GetModelLocation();
	m_UniformProjection = m_Shader->GetProjectionLocation();
	m_UniformView = m_Shader->GetViewLocation();
	m_UniformMatSpecularInstensity = m_Shader->GetMatSpecularIntensityLocation();
	m_UniformMatShininess = m_Shader->GetMatShininessLocation();
	m_UniformCameraPosition = m_Shader->GetCameraPositionLocation();

}

void Renderer::DrawData(GLuint uniformModel, glm::mat4 modelMatrix, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, Camera* mainCamera, RenderableData* renderData)
{
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	m_Material->UseMaterial(m_UniformMatSpecularInstensity, m_UniformMatShininess);

	if (renderData->TextureData != NULL)
	{
		renderData->TextureData->UseTexture();
	}
	renderData->Renderable->Render();
}

void Renderer::RenderObjectWithShader(glm::mat4 modelMatrix, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, Camera* mainCamera, RenderableData* renderData)
{
	m_Shader->SetTextureUnit(1);
	m_Shader->UseShader();

	glUniform3f(m_UniformCameraPosition, mainCamera->GetCameraPosition().x, mainCamera->GetCameraPosition().y, mainCamera->GetCameraPosition().z);
	glUniformMatrix4fv(m_UniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(m_UniformView, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	DrawData(m_UniformModel, modelMatrix, projectionMatrix, viewMatrix, mainCamera, renderData);
}
