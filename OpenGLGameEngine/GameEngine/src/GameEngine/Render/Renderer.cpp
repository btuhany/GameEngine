#include "Renderer.h"

namespace GameEngine
{
	Renderer::Renderer()
	{
		EventManager::GetInstance().Subscribe<ComponentEvent>(
			[this](std::shared_ptr<ComponentEvent> event) {
			this->onComponentEvent(event);
			}, 10);
		EventManager::GetInstance().Subscribe<SceneCameraChangedEvent>(
			[this](std::shared_ptr<SceneCameraChangedEvent> eventData) {
				this->onSceneCameraChangedEvent(eventData);
			}, 10);
	}
	Renderer::~Renderer()
	{
		EventManager::GetInstance().Unsubscribe<ComponentEvent>([this](std::shared_ptr<ComponentEvent> event) {
			this->onComponentEvent(event);
			});
		EventManager::GetInstance().Unsubscribe<SceneCameraChangedEvent>([this](std::shared_ptr<SceneCameraChangedEvent> event) {
			this->onSceneCameraChangedEvent(event);
			});
	}
	void Renderer::Initialize(Scene* scene, GLfloat bufferRatio)
	{
		if (!(scene->IsInitialized()))
		{
			LOG_CORE_ERROR("Renderer | Initialize | Scene not initialized!");
			return;
		}
		m_Skybox = scene->getSkybox();
		m_Camera = scene->getCamera();
		m_DirLight = scene->getDirectionalLight();
		m_BackgroundColor = scene->getBackgroundColor();
		m_DirLightShadowShader = scene->getDirectionalLightShadowShader();
		m_OmniShadowShader = scene->getOmniShadowShader();
		m_Scene = scene;
		m_BufferRatio = bufferRatio;
		m_IsInitialized = true;
	}

	void Renderer::Draw(bool shadowPassActive, bool renderDirLightShadow, bool renderOmniLightShadow)
	{
		glm::mat4 projection = m_Scene->getCamera()->
			CalcGetProjectionMatrix(m_BufferRatio);
		if (shadowPassActive)
		{
			if (renderDirLightShadow)
				DirectionalShadowMapPass(m_DirLight);
			if (renderOmniLightShadow)
				OmniShadowMapPass(m_OmniShadowShader, m_Scene->m_PointLightList, m_Scene->getPointLightCount(),
					m_Scene->m_SpotLightList, m_Scene->getSpotLightCount());
		}
		RenderPass(projection, m_Scene->m_PointLightList, m_Scene->getPointLightCount(),
			m_Scene->m_SpotLightList, m_Scene->getSpotLightCount());

#if _DEBUG
		if (SETTINGS_DEBUG_MODE)
		{
			DebugPass(projection);
		}
#endif
	}

	void Renderer::DebugPass(glm::mat4 projectionMatrix)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		for (const auto& pair : Renderer::DebugMeshRenderDataTransformMap)
		{
			auto transformWeakPtr = pair.second;
			if (transformWeakPtr.expired())
			{
				//TODO get expired list and remove from map after
				continue;
			}
			auto transform = transformWeakPtr.lock();
			auto modelMat = transform->GetModelMatrix();
			glm::mat4 offsetModel = glm::translate(
				glm::mat4(1.0f), glm::vec3(transform->getPosition().x, transform->getPosition().y, transform->getPosition().z + 0.1f)) * 
				glm::mat4(transform->getRotation());

			auto debugMeshRenderData = pair.first;
			auto debugShader = debugMeshRenderData->shader;
			debugShader->UseShader();

			glUniform3f(debugShader->GetCameraPositionLocation(), m_Camera->getPosition().x, m_Camera->getPosition().y, m_Camera->getPosition().z);
			glUniformMatrix4fv(debugShader->GetProjectionLocation(), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
			glUniformMatrix4fv(debugShader->GetViewLocation(), 1, GL_FALSE, glm::value_ptr(m_Camera->CalculateViewMatrix()));
			glUniformMatrix4fv(debugMeshRenderData->shader->GetModelLocation(), 1, GL_FALSE, glm::value_ptr(offsetModel));
			auto meshData = debugMeshRenderData->mesh;
			glBindVertexArray(meshData->GetVAO());
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshData->GetIBO());
			glDrawElements(GL_TRIANGLES, meshData->GetIndexCount(), GL_UNSIGNED_INT, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

		}
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	void Renderer::RenderPass(glm::mat4 projectionMatrix, PointLight* pLightList, unsigned int plightCount, SpotLight* sLightList, unsigned int slightCount)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, 1920, 1080);
		//Clear window
		glClearColor(m_BackgroundColor.x, m_BackgroundColor.y, m_BackgroundColor.z, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (m_Skybox != nullptr)
		{
			m_Skybox->DrawSkybox(m_Camera->CalculateViewMatrix(), projectionMatrix);
		}

		for (size_t i = 0; i < m_RendererComponents.size(); i++)
		{
			auto renderComponent = m_RendererComponents[i];
			if (!isAbleToRender(renderComponent)) 
			{
				continue;
			}

		//Set point lights
			renderComponent->getRenderDataShader()->UseShader();
			renderComponent->getRenderDataShader()->SetPointLights(pLightList, plightCount, 4, 0);
		

		//Set spot lights
			renderComponent->getRenderDataShader()->UseShader();
			renderComponent->getRenderDataShader()->SetSpotLights(sLightList, slightCount, 4 + plightCount, plightCount);
		

		//Render scene
			auto renderShader = renderComponent->getRenderDataShader();
			renderShader->UseShader();

			glUniform3f(renderShader->GetCameraPositionLocation(), m_Camera->getPosition().x, m_Camera->getPosition().y, m_Camera->getPosition().z);
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
				if (m_DirLight->getShadowMap() != nullptr)
				{
					m_DirLight->getShadowMap()->Read(GL_TEXTURE3);
					renderShader->SetDirectionalShadowMap(3);
				}
			}

			renderShader->Validate();
			renderComponent->Render(renderComponent->getRenderDataShader()->GetModelLocation());
		}
	}

	void Renderer::DirectionalShadowMapPass(std::shared_ptr<DirectionalLight> dLight)
	{
		if (dLight == nullptr)
		{
			LOG_CORE_WARN("Directional light not initialized!");
			return;
		}

		if (dLight->getShadowMap() == nullptr)
		{
			LOG_CORE_WARN("Directional light has no shadow map");
			return;
		}

		glViewport(0, 0, dLight->getShadowMap()->getShadowWidth(), dLight->getShadowMap()->getShadowHeight());
		dLight->getShadowMap()->Write();
		glClear(GL_DEPTH_BUFFER_BIT);

		//RenderSceneShadowMap
		for (size_t i = 0; i < m_RendererComponents.size(); i++)
		{
			if (!isAbleToRender(m_RendererComponents[i]))
			{
				continue;
			}

			if (m_DirLightShadowShader == nullptr)
			{
				LOG_CORE_ERROR("Directional shadow shader is null!");
				return;
			}
			m_DirLightShadowShader->UseShader();
			glm::mat4 lightTransform = m_DirLight->CalculateLightTransform();
			m_DirLightShadowShader->SetDirectionalLightTransform(&lightTransform);
			m_DirLightShadowShader->Validate();

			if (m_RendererComponents[i]->IsShadowRenderable())
				m_RendererComponents[i]->Render(m_DirLightShadowShader->GetModelLocation());
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	void Renderer::OmniShadowMapPass(std::shared_ptr<Shader> omniShadowShader, PointLight* pLightList, unsigned int plightCount, SpotLight* sLightList, unsigned int slightCount)
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
			if (pLightList[i].getShadowMap() == nullptr)
			{
				continue;
			}

			glViewport(0, 0, pLightList[i].getShadowMap()->getShadowWidth(), pLightList[i].getShadowMap()->getShadowHeight());
			pLightList[i].getShadowMap()->Write(); //Bind framebuffer
			glClear(GL_DEPTH_BUFFER_BIT);

			for (size_t j = 0; j < m_RendererComponents.size(); j++)
			{
				if (!isAbleToRender(m_RendererComponents[j]))
				{
					continue;
				}
				auto pointLight = &pLightList[i];
				//m_RendererComponents[j]->RenderToPointLightShadowMap(&pLightList[i]);
				glUniform3f(m_OmniShadowShader->GetOmniLightPosLocation(), pointLight->GetPosition().x, pointLight->GetPosition().y, pointLight->GetPosition().z);
				glUniform1f(m_OmniShadowShader->GetFarPlaneLocation(), pointLight->GetFarPlane());
				m_OmniShadowShader->SetLightMatrices(pointLight->CalculateLightTransform());

				if (m_RendererComponents[j]->IsShadowRenderable())
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
			if (sLightList[i].getShadowMap() == nullptr)
			{
				continue;
			}

			glViewport(0, 0, sLightList[i].getShadowMap()->getShadowWidth(), sLightList[i].getShadowMap()->getShadowHeight());
			sLightList[i].getShadowMap()->Write();  //Bind framebuffer
			glClear(GL_DEPTH_BUFFER_BIT);

			for (size_t j = 0; j < m_RendererComponents.size(); j++)
			{
				if (!isAbleToRender(m_RendererComponents[j]))
				{
					continue;
				}
				auto spotLight = &sLightList[i];
				//m_RendererComponents[j]->RenderToPointLightShadowMap(&sLightList[i]);
				glUniform3f(m_OmniShadowShader->GetOmniLightPosLocation(), spotLight->GetPosition().x, spotLight->GetPosition().y, spotLight->GetPosition().z);
				glUniform1f(m_OmniShadowShader->GetFarPlaneLocation(), spotLight->GetFarPlane());
				m_OmniShadowShader->SetLightMatrices(spotLight->CalculateLightTransform());

				if (m_RendererComponents[j]->IsShadowRenderable())
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
	void Renderer::onComponentEvent(std::shared_ptr<ComponentEvent> componentEvent)
	{
		if (componentEvent->compAction == ComponentAction::Added)
		{
			auto componentType = componentEvent->comp->getType();
			if (componentType == ComponentType::Renderer)
			{
				auto rendererComponent = std::static_pointer_cast<RendererComponent>(componentEvent->comp);
				m_RendererComponents.push_back(rendererComponent);
			}
		}
		else if (componentEvent->compAction == ComponentAction::OwnerPreDestroyed)
		{
			auto componentType = componentEvent->comp->getType();
			if (componentType == ComponentType::Renderer)
			{
				auto rendererComponent = std::static_pointer_cast<RendererComponent>(componentEvent->comp);
				auto it = std::find(m_RendererComponents.begin(), m_RendererComponents.end(), rendererComponent);
				if (it != m_RendererComponents.end())
				{
					m_RendererComponents.erase(it);
				}
			}
		}
	}

	void Renderer::onSceneCameraChangedEvent(std::shared_ptr<SceneCameraChangedEvent> sceneCameraChangedEventData)
	{
		m_Camera = sceneCameraChangedEventData->camera;
	}

	bool Renderer::isAbleToRender(std::shared_ptr<RendererComponent> rendererComponent)
	{
		if (rendererComponent->getEntity().expired())
		{
			return false;
		}
		auto ownerEntity = rendererComponent->getEntity().lock();
		//std::cout << "renderer object name: " << ownerEntity->getName() << ", object active: " << ownerEntity->getActive() << " , compnentEnabled: " << rendererComponent->getEnabled() << std::endl;
		return rendererComponent->getEnabled() && ownerEntity->getActive();  //Scene control in the future
	}

	std::unordered_map<std::shared_ptr<DebugRenderData>, std::weak_ptr<Transform>> Renderer::DebugMeshRenderDataTransformMap;
}
