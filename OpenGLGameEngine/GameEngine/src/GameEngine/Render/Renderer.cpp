#include "Renderer.h"

namespace GameEngine
{
	//Renderer::Renderer(std::shared_ptr<Skybox> skybox, glm::vec3 backgroundColor, std::shared_ptr<Camera> camera)
	//{
	//	m_Skybox = skybox;
	//	m_Camera = camera;
	//	m_BackgroundColor = backgroundColor;
	//}

	void Renderer::Initialize(Scene* scene)
	{
		//TODO is scene not initialized throw error
		m_Skybox = scene->GetSkybox();
		m_Camera = scene->GetCamera();
		m_BackgroundColor = scene->GetBackgroundColor();
		m_IsInitialized = true;
	}

	//void Renderer::Render()
	//{
	//	//if (m_ShadowPassActive)
	//	//{
	//	//	if (m_RenderDirLightShadowMap)
	//	//		directionalShadowMapPass()
	//	//}
	//}

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
		for (size_t i = 0; i < RenderableMeshEntitiesPublic.size(); i++)
		{
			RenderableMeshEntitiesPublic[i]->renderer->meshRenderData->shader->UseShader();
			RenderableMeshEntitiesPublic[i]->renderer->meshRenderData->shader->SetPointLights(pLightList, plightCount, 4, 0);
		}
		for (size_t i = 0; i < RenderableModelEntitiesPublic.size(); i++)
		{
			RenderableModelEntitiesPublic[i]->renderer->modelRenderData->shader->UseShader();
			RenderableModelEntitiesPublic[i]->renderer->modelRenderData->shader->SetPointLights(pLightList, plightCount, 4, 0);
		}

		//Set spot lights
		for (size_t i = 0; i < RenderableMeshEntitiesPublic.size(); i++)
		{
			RenderableMeshEntitiesPublic[i]->renderer->meshRenderData->shader->UseShader();
			RenderableMeshEntitiesPublic[i]->renderer->meshRenderData->shader->SetSpotLights(sLightList, slightCount, 4 + plightCount, plightCount);
		}
		for (size_t i = 0; i < RenderableModelEntitiesPublic.size(); i++)
		{
			RenderableModelEntitiesPublic[i]->renderer->modelRenderData->shader->UseShader();
			RenderableModelEntitiesPublic[i]->renderer->modelRenderData->shader->SetSpotLights(sLightList, slightCount, 4 + plightCount, plightCount);
		}

		//Render scene
		for (size_t i = 0; i < RenderableMeshEntitiesPublic.size(); i++)
		{
			RenderableMeshEntitiesPublic[i]->Render(projectionMatrix);
		}

		for (size_t i = 0; i < RenderableModelEntitiesPublic.size(); i++)
		{
			RenderableModelEntitiesPublic[i]->Render(projectionMatrix);
		}
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
		for (size_t i = 0; i < RenderableMeshEntitiesPublic.size(); i++)
		{
			RenderableMeshEntitiesPublic[i]->renderer->RenderToDirLightShadowMap();
		}
		for (size_t i = 0; i < RenderableModelEntitiesPublic.size(); i++)
		{
			RenderableModelEntitiesPublic[i]->renderer->RenderToDirLightShadowMap();
		}
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

			for (size_t j = 0; j < RenderableMeshEntitiesPublic.size(); j++)
			{
				RenderableMeshEntitiesPublic[j]->renderer->RenderToPointLightShadowMap(&pLightList[i]);
			}
			for (size_t i = 0; i < RenderableModelEntitiesPublic.size(); i++)
			{
				RenderableModelEntitiesPublic[i]->renderer->RenderToPointLightShadowMap(&pLightList[i]);
			}
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

			for (size_t j = 0; j < RenderableMeshEntitiesPublic.size(); j++)
			{
				RenderableMeshEntitiesPublic[j]->renderer->RenderToPointLightShadowMap(&sLightList[i]);
			}
			for (size_t i = 0; i < RenderableModelEntitiesPublic.size(); i++)
			{
				RenderableModelEntitiesPublic[i]->renderer->RenderToPointLightShadowMap(&sLightList[i]);
			}
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}
}
