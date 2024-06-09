#include "Renderer.h"


Renderer::Renderer()
{
}

Renderer::~Renderer()
{
	printf("deleted renderer");
	delete m_Shader;
	delete m_DirShadowShader;
	delete m_OmniShadowShader;
}

Renderer::Renderer(Shader* shader, Shader* dirShadowShader, Shader* omniShadowShader)
{
	m_Shader = shader;
	m_DirShadowShader = dirShadowShader;
	m_OmniShadowShader = omniShadowShader;
	m_UniformModel = m_Shader->GetModelLocation();
	m_UniformProjection = m_Shader->GetProjectionLocation();
	m_UniformView = m_Shader->GetViewLocation();
	m_UniformMatSpecularInstensity = m_Shader->GetMatSpecularIntensityLocation();
	m_UniformMatShininess = m_Shader->GetMatShininessLocation();
	m_UniformCameraPosition = m_Shader->GetCameraPositionLocation();

}

void Renderer::DrawData(GLuint uniformModel, glm::mat4 modelMatrix, RenderableData* renderData)
{
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	renderData->MaterialData->UseMaterial(m_UniformMatSpecularInstensity, m_UniformMatShininess);

	if (renderData->TextureData != NULL)
	{
		renderData->TextureData->UseTexture();
	}
	renderData->Renderable->Render();
}

void Renderer::RenderObjectWithShader(glm::mat4 modelMatrix, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, Camera* mainCamera, RenderableData* renderData, DirectionalLight* directionalLight)
{
	//m_Shader->UseShader();

	glUniform3f(m_Shader->GetCameraPositionLocation(), mainCamera->GetCameraPosition().x, mainCamera->GetCameraPosition().y, mainCamera->GetCameraPosition().z);
	glUniformMatrix4fv(m_Shader->GetProjectionLocation(), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(m_Shader->GetViewLocation(), 1, GL_FALSE, glm::value_ptr(viewMatrix));
	
	m_Shader->SetTextureUnit(2);
	if (directionalLight != nullptr)
	{
		m_Shader->SetDirectionalLight(directionalLight);
		m_Shader->SetDirectionalLightTransform(&m_LightTransform);
		directionalLight->GetShadowMap()->Read(GL_TEXTURE3);
		m_Shader->SetDirectionalShadowMap(3);
	}



	m_Shader->Validate();


	DrawData(m_Shader->GetModelLocation(), modelMatrix, renderData);
}

void Renderer::RenderObjectForDirectionalShadow(glm::mat4 modelMatrix, DirectionalLight* directionalLight, RenderableData* renderData)
{
	m_DirShadowShader->UseShader();

	m_LightTransform = directionalLight->CalculateLightTransform();
	m_DirShadowShader->SetDirectionalLightTransform(&m_LightTransform);
	m_DirShadowShader->Validate();

	DrawData(m_DirShadowShader->GetModelLocation(), modelMatrix, renderData);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
}

void Renderer::RenderObjectForOmniShadow(glm::mat4 modelMatrix, PointLight* pointLight, RenderableData* renderData)
{
	//m_OmniShadowShader->UseShader();

	glUniform3f(m_OmniShadowShader->GetOmniLightPosLocation(), pointLight->GetPosition().x, pointLight->GetPosition().y, pointLight->GetPosition().z);
	glUniform1f(m_OmniShadowShader->GetFarPlaneLocation(), pointLight->GetFarPlane());
	m_OmniShadowShader->SetLightMatrices(pointLight->CalculateLightTransform());

	DrawData(m_OmniShadowShader->GetModelLocation(), modelMatrix, renderData);


}
