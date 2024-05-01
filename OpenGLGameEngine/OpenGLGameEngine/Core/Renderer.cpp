#include "Renderer.h"


Renderer::Renderer()
{
}

Renderer::~Renderer()
{
	m_Mesh = nullptr;
	m_Texture = nullptr;
	m_Material = nullptr;
	m_Model = nullptr;
}

Renderer::Renderer(Model* model, Material* material, Shader* shader)
{
	m_Model = model;
	m_Material = material;
	m_Shader = shader;
}

Renderer::Renderer(Mesh* mesh, Texture* texture, Material* material, Shader* shader)
{
	m_Mesh = mesh;
	m_Texture = texture;
	m_Material = material;
	m_Shader = shader;
}

void Renderer::RenderUpdate(glm::mat4 modelMatrix, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, Camera* mainCamera)
{
	m_Shader->UseShader();
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
	m_Shader->SetTexture(1);
	m_Shader->UseShader();

	if (m_Model == nullptr)
	{
		m_Texture->UseTexture();
		m_Material->UseMaterial(uniformMatSpecularInstensity, uniformMatShininess);
		m_Mesh->RenderMesh();
	}
	else
	{
		m_Material->UseMaterial(uniformMatSpecularInstensity, uniformMatShininess);
		m_Model->RenderModel();
	}
}
