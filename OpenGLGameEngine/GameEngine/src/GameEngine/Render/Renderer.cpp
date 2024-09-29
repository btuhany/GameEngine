#include "Renderer.h"

namespace GameEngine
{
	Renderer::Renderer()
	{
		EventManager::GetInstance().Subscribe<ComponentEvent>(
			[this](std::shared_ptr<ComponentEvent> event) {
			this->onComponentAssigned(event);
			}, 10);
	}
	Renderer::~Renderer()
	{
		EventManager::GetInstance().Unsubscribe<ComponentEvent>([this](std::shared_ptr<ComponentEvent> event) {
			this->onComponentAssigned(event);
			});
	}
	void Renderer::Initialize(Scene* scene)
	{
		//TODO is scene not initialized throw error
		m_Skybox = scene->GetSkybox();
		m_Camera = scene->GetCamera();
		m_DirLight = scene->GetDirectionalLight();
		m_BackgroundColor = scene->GetBackgroundColor();
		m_DirLightShadowShader = scene->m_DirLightShadowShader;
		m_OmniShadowShader = scene->m_OmniShadowShader;
		m_IsInitialized = true;
	}

	void Renderer::renderPass(glm::mat4 projectionMatrix, PointLight* pLightList, unsigned int plightCount, SpotLight* sLightList, unsigned int slightCount)
	{
		//TODO Initialize check;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, 1366, 768);
		//Clear window
		glClearColor(m_BackgroundColor.x, m_BackgroundColor.y, m_BackgroundColor.z, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (m_Skybox != nullptr)
		{
			m_Skybox->DrawSkybox(m_Camera->CalculateViewMatrix(), projectionMatrix);
		}

		//Set point lights
		for (size_t i = 0; i < m_RendererComponents.size(); i++)
		{
			m_RendererComponents[i]->GetRenderDataShader()->UseShader();
			m_RendererComponents[i]->GetRenderDataShader()->SetPointLights(pLightList, plightCount, 4, 0);
		}
		//for (size_t i = 0; i < m_meshRendererComponents.size(); i++)
		//{
		//	m_meshRendererComponents[i]->meshRenderData->shader->UseShader();
		//	m_meshRendererComponents[i]->meshRenderData->shader->SetPointLights(pLightList, plightCount, 4, 0);
		//}
		//for (size_t i = 0; i < m_modelRendererComponents.size(); i++)
		//{
		//	m_modelRendererComponents[i]->modelRenderData->shader->UseShader();
		//	m_modelRendererComponents[i]->modelRenderData->shader->SetPointLights(pLightList, plightCount, 4, 0);
		//}

		//Set spot lights
		for (size_t i = 0; i < m_RendererComponents.size(); i++)
		{
			m_RendererComponents[i]->GetRenderDataShader()->UseShader();
			m_RendererComponents[i]->GetRenderDataShader()->SetSpotLights(sLightList, slightCount, 4 + plightCount, plightCount);
		}
		//for (size_t i = 0; i < m_meshRendererComponents.size(); i++)
		//{
		//	m_meshRendererComponents[i]->meshRenderData->shader->UseShader();
		//	m_meshRendererComponents[i]->meshRenderData->shader->SetSpotLights(sLightList, slightCount, 4 + plightCount, plightCount);
		//}
		//for (size_t i = 0; i < m_modelRendererComponents.size(); i++)
		//{
		//	m_modelRendererComponents[i]->modelRenderData->shader->UseShader();
		//	m_modelRendererComponents[i]->modelRenderData->shader->SetSpotLights(sLightList, slightCount, 4 + plightCount, plightCount);
		//}

		//Render scene
		for (size_t i = 0; i < m_RendererComponents.size(); i++)
		{

			//m_RendererComponents[i]->Render(projectionMatrix);
			auto renderShader = m_RendererComponents[i]->GetRenderDataShader();
			renderShader->UseShader();

			glUniform3f(renderShader->GetCameraPositionLocation(), m_Camera->GetCameraPosition().x, m_Camera->GetCameraPosition().y, m_Camera->GetCameraPosition().z);
			glUniformMatrix4fv(renderShader->GetProjectionLocation(), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
			glUniformMatrix4fv(renderShader->GetViewLocation(), 1, GL_FALSE, glm::value_ptr(m_Camera->CalculateViewMatrix()));

			renderShader->SetTextureUnit(2);

			//Bind directional light for shader
			if (m_DirLight != nullptr)
			{
				renderShader->SetDirectionalLight(m_DirLight);
				//TODO: should be in if
				glm::mat4 lightTransform = m_DirLight->CalculateLightTransform();
				renderShader->SetDirectionalLightTransform(&lightTransform);
				if (m_DirLight->GetShadowMap() != nullptr)
				{
					m_DirLight->GetShadowMap()->Read(GL_TEXTURE3);
					renderShader->SetDirectionalShadowMap(3);
				}
			}

			renderShader->Validate();
			m_RendererComponents[i]->Render(m_RendererComponents[i]->GetRenderDataShader()->GetModelLocation());
		}

		//for (size_t i = 0; i < m_meshRendererComponents.size(); i++)
		//{
		//	m_meshRendererComponents[i]->Render(projectionMatrix);
		//}
		//for (size_t i = 0; i < m_modelRendererComponents.size(); i++)
		//{
		//	m_modelRendererComponents[i]->Render(projectionMatrix);
		//}
	}

	void Renderer::directionalShadowMapPass(DirectionalLight* dLight)
	{
		if (dLight == nullptr)
		{
			LOG_CORE_WARN("Directional light not initialized!");
			return;
		}

		if (dLight->GetShadowMap() == nullptr)
		{
			LOG_CORE_WARN("Directional light has no shadow map");
			return;
		}

		glViewport(0, 0, dLight->GetShadowMap()->GetShadowWidth(), dLight->GetShadowMap()->GetShadowHeight());
		dLight->GetShadowMap()->Write();
		glClear(GL_DEPTH_BUFFER_BIT);

		//RenderSceneShadowMap
		for (size_t i = 0; i < m_RendererComponents.size(); i++)
		{
			//m_RendererComponents[i]->RenderToDirLightShadowMap();
			if (m_DirLightShadowShader == nullptr)
			{
				LOG_CORE_ERROR("Directional shadow shader is null!");
				return;
			}
			m_DirLightShadowShader->UseShader();
			glm::mat4 lightTransform = m_DirLight->CalculateLightTransform();
			m_DirLightShadowShader->SetDirectionalLightTransform(&lightTransform);
			m_DirLightShadowShader->Validate();

			m_RendererComponents[i]->Render(m_DirLightShadowShader->GetModelLocation());
		}
		//for (size_t i = 0; i < m_meshRendererComponents.size(); i++)
		//{
		//	m_meshRendererComponents[i]->RenderToDirLightShadowMap();
		//}
		//for (size_t i = 0; i < m_modelRendererComponents.size(); i++)
		//{
		//	m_modelRendererComponents[i]->RenderToDirLightShadowMap();
		//}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	void Renderer::omniShadowMapPass(Shader* omniShadowShader, PointLight* pLightList, unsigned int plightCount, SpotLight* sLightList, unsigned int slightCount)
	{
		if (plightCount + slightCount == 0)
		{
			LOG_CORE_WARN("There aren't any lights to render omni shadows!");
			return;
		}
		if (omniShadowShader == nullptr)
		{
			LOG_CORE_WARN("Trying to render the omni shadow map, but the shadow shader isn't set!");
			return;
		}

		omniShadowShader->UseShader();
		for (size_t i = 0; i < plightCount; i++)
		{
			if (pLightList[i].GetShadowMap() == nullptr)
			{
				continue;
			}

			glViewport(0, 0, pLightList[i].GetShadowMap()->GetShadowWidth(), pLightList[i].GetShadowMap()->GetShadowHeight());
			pLightList[i].GetShadowMap()->Write(); //Bind framebuffer
			glClear(GL_DEPTH_BUFFER_BIT);

			for (size_t j = 0; j < m_RendererComponents.size(); j++)
			{
				auto pointLight = &pLightList[i];
				//m_RendererComponents[j]->RenderToPointLightShadowMap(&pLightList[i]);
				glUniform3f(m_OmniShadowShader->GetOmniLightPosLocation(), pointLight->GetPosition().x, pointLight->GetPosition().y, pointLight->GetPosition().z);
				glUniform1f(m_OmniShadowShader->GetFarPlaneLocation(), pointLight->GetFarPlane());
				m_OmniShadowShader->SetLightMatrices(pointLight->CalculateLightTransform());

				m_RendererComponents[j]->Render(m_OmniShadowShader->GetModelLocation());
			}
			//for (size_t j = 0; j < m_meshRendererComponents.size(); j++)
			//{
			//	m_meshRendererComponents[j]->RenderToPointLightShadowMap(&pLightList[i]);
			//}
			//for (size_t j = 0; j < m_modelRendererComponents.size(); j++)
			//{
			//	m_modelRendererComponents[j]->RenderToPointLightShadowMap(&pLightList[i]);
			//}
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
		for (size_t i = 0; i < slightCount; i++)
		{
			if (sLightList[i].GetShadowMap() == nullptr)
			{
				continue;
			}

			glViewport(0, 0, sLightList[i].GetShadowMap()->GetShadowWidth(), sLightList[i].GetShadowMap()->GetShadowHeight());
			sLightList[i].GetShadowMap()->Write();  //Bind framebuffer
			glClear(GL_DEPTH_BUFFER_BIT);

			for (size_t j = 0; j < m_RendererComponents.size(); j++)
			{
				auto spotLight = &sLightList[i];
				//m_RendererComponents[j]->RenderToPointLightShadowMap(&sLightList[i]);
				glUniform3f(m_OmniShadowShader->GetOmniLightPosLocation(), spotLight->GetPosition().x, spotLight->GetPosition().y, spotLight->GetPosition().z);
				glUniform1f(m_OmniShadowShader->GetFarPlaneLocation(), spotLight->GetFarPlane());
				m_OmniShadowShader->SetLightMatrices(spotLight->CalculateLightTransform());

				m_RendererComponents[j]->Render(m_OmniShadowShader->GetModelLocation());
			}
			//for (size_t j = 0; j < m_meshRendererComponents.size(); j++)
			//{
			//	m_meshRendererComponents[j]->RenderToPointLightShadowMap(&sLightList[i]);
			//}
			//for (size_t j = 0; j < m_modelRendererComponents.size(); j++)
			//{
			//	m_modelRendererComponents[j]->RenderToPointLightShadowMap(&sLightList[i]);
			//}
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}
	void Renderer::onComponentAssigned(std::shared_ptr<ComponentEvent> componentEvent)
	{
		if (componentEvent->CompAction == ComponentAction::Added)
		{
			auto componentType = componentEvent->Comp->GetType();
			if (componentType == ComponentType::Renderer)
			{
				auto rendererComponent = std::static_pointer_cast<RendererComponent>(componentEvent->Comp);
				m_RendererComponents.push_back(rendererComponent);
			}
		}
	}

}
