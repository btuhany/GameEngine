#include "MeshRenderer.h"
namespace GameEngine {
	std::vector<MeshRenderer*> MeshRenderer::m_RendererList;

	MeshRenderer::MeshRenderer() : Renderer()
	{
	}

	MeshRenderer::~MeshRenderer()
	{
		printf("deleted renderer \n");
		delete m_Shader;
		delete m_DirShadowShader;
		delete m_OmniShadowShader;
	}

	MeshRenderer::MeshRenderer(Shader* shader, Shader* dirShadowShader, Shader* omniShadowShader) : Renderer(shader)
	{

		m_Shader->SetUseDirLightShadow(true);
		m_DirShadowShader = dirShadowShader;
		m_OmniShadowShader = omniShadowShader;

		m_UniformView = m_Shader->GetViewLocation();
		m_UniformMatSpecularInstensity = m_Shader->GetMatSpecularIntensityLocation();
		m_UniformMatShininess = m_Shader->GetMatShininessLocation();
		m_UniformCameraPosition = m_Shader->GetCameraPositionLocation();
		m_RendererList.push_back(this);
	}

	MeshRenderer::MeshRenderer(Shader* shader, Shader* omniShadowShader) : Renderer(shader)
	{

		m_Shader->SetUseDirLightShadow(false);
		m_Shader->SetDirectionalShadowMap(3); //setting the uniform sampler2D to texture unit 3 (texture unit 0 is default and causes to not render properly)
		m_DirShadowShader = nullptr;
		m_OmniShadowShader = omniShadowShader;

		m_UniformView = m_Shader->GetViewLocation();
		m_UniformMatSpecularInstensity = m_Shader->GetMatSpecularIntensityLocation();
		m_UniformMatShininess = m_Shader->GetMatShininessLocation();
		m_UniformCameraPosition = m_Shader->GetCameraPositionLocation();
		m_RendererList.push_back(this);
	}

	MeshRenderer::MeshRenderer(Shader* shader) : Renderer(shader)
	{

		m_Shader->SetUseDirLightShadow(false);
		m_Shader->SetDirectionalShadowMap(3); //setting the uniform sampler2D to texture unit 3 (texture unit 0 is default and causes to not render properly)
		m_DirShadowShader = nullptr;
		m_OmniShadowShader = nullptr;

		m_UniformView = m_Shader->GetViewLocation();
		m_UniformMatSpecularInstensity = m_Shader->GetMatSpecularIntensityLocation();
		m_UniformMatShininess = m_Shader->GetMatShininessLocation();
		m_UniformCameraPosition = m_Shader->GetCameraPositionLocation();
		m_RendererList.push_back(this);
	}

	void MeshRenderer::Initialize(Camera* camera, DirectionalLight* light)
	{
		m_Camera = camera;
		m_DirLight = light;
	}

	void MeshRenderer::DrawData(GLuint uniformModel, glm::mat4 modelMatrix, RenderableData* renderData)
	{
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelMatrix));

		renderData->MaterialData->UseMaterial(m_UniformMatSpecularInstensity, m_UniformMatShininess);

		if (renderData->TextureData != NULL)
		{
			renderData->TextureData->UseTexture();
		}
		renderData->Renderable->Render();
	}

	void MeshRenderer::RenderObjectWithShader(glm::mat4 modelMatrix, glm::mat4 projectionMatrix, RenderableData* renderData)
	{
		//m_Shader->UseShader();

		glUniform3f(m_Shader->GetCameraPositionLocation(), m_Camera->GetCameraPosition().x, m_Camera->GetCameraPosition().y, m_Camera->GetCameraPosition().z);
		glUniformMatrix4fv(m_Shader->GetProjectionLocation(), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		glUniformMatrix4fv(m_Shader->GetViewLocation(), 1, GL_FALSE, glm::value_ptr(m_Camera->CalculateViewMatrix()));

		m_Shader->SetTextureUnit(2);
		if (m_DirLight != nullptr)
		{
			m_Shader->SetDirectionalLight(m_DirLight);
			//TODO: should be in if
			m_Shader->SetDirectionalLightTransform(&m_LightTransform);
			if (m_DirLight->GetShadowMap() != nullptr)
			{
				m_DirLight->GetShadowMap()->Read(GL_TEXTURE3);
				m_Shader->SetDirectionalShadowMap(3);
			}

		}



		m_Shader->Validate();


		DrawData(m_Shader->GetModelLocation(), modelMatrix, renderData);
	}

	void MeshRenderer::RenderObjectForDirectionalShadow(glm::mat4 modelMatrix, DirectionalLight* directionalLight, RenderableData* renderData)
	{
		if (m_DirShadowShader == nullptr)
		{
			LOG_CORE_ERROR("Directional shadow shader is null!");
			return;
		}
		m_DirShadowShader->UseShader();

		m_LightTransform = directionalLight->CalculateLightTransform();
		m_DirShadowShader->SetDirectionalLightTransform(&m_LightTransform);
		m_DirShadowShader->Validate();

		DrawData(m_DirShadowShader->GetModelLocation(), modelMatrix, renderData);
	}

	void MeshRenderer::RenderObjectForOmniShadow(glm::mat4 modelMatrix, PointLight* pointLight, RenderableData* renderData)
	{
		//m_OmniShadowShader->UseShader();
		glUniform3f(m_OmniShadowShader->GetOmniLightPosLocation(), pointLight->GetPosition().x, pointLight->GetPosition().y, pointLight->GetPosition().z);
		glUniform1f(m_OmniShadowShader->GetFarPlaneLocation(), pointLight->GetFarPlane());
		m_OmniShadowShader->SetLightMatrices(pointLight->CalculateLightTransform());

		DrawData(m_OmniShadowShader->GetModelLocation(), modelMatrix, renderData);


	}

	Shader* MeshRenderer::GetRenderShader()
	{
		return m_Shader;
	}

	void MeshRenderer::ClearRenderers()
	{
		for (int i = 0; i < m_RendererList.size();i++)
		{
			delete (m_RendererList[i]);
		}
		m_RendererList.clear();
	}
}