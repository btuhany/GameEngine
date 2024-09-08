#include "Scene.h"
namespace GameEngine {
	Scene::Scene()
	{
		m_BackgroundColour = glm::vec3(0.0f, 0.0f, 0.0f);
		m_UseSkybox = false;
		m_MainCamera = nullptr;
		m_DirectionalLight = nullptr;
		m_Skybox = nullptr;
		m_OmniShadowShader = nullptr;
	}

	Scene::~Scene()
	{
		printf("\n deleted scene \n");
		delete m_DirectionalLight;
		delete m_MainCamera;
		//TODO: m_ShadowMapRenderableObject clear?
		//for (auto obj : m_RenderableObjectList) {
		//	obj->ClearRenderableObject();
		//}
		//m_RenderableObjectList.clear();
		//MeshRenderer::ClearRenderers();
	}

	void Scene::Initialize()
	{
		printf("scene");
	}

	void Scene::Start()
	{
	}

	void Scene::Update(GLfloat deltaTime)
	{

	}

	Camera* Scene::GetCamera()
	{
		return m_MainCamera;
	}

	std::shared_ptr<Skybox> Scene::GetSkybox()
	{
		return m_Skybox;
	}

	glm::vec3 Scene::GetBackgroundColor()
	{
		return m_BackgroundColour;
	}

	bool Scene::UseSkyboxActive()
	{
		return m_UseSkybox;
	}

	void Scene::RenderScene(glm::mat4 projection)
	{

		for (size_t i = 0; i < RenderableMeshEntitiesPublic.size(); i++)
		{
			RenderableMeshEntitiesPublic[i]->Render(projection);
		}

		for (size_t i = 0; i < RenderableModelEntitiesPublic.size(); i++)
		{
			RenderableModelEntitiesPublic[i]->Render(projection);
		}
	}

	void Scene::SetPointLights()
	{
		for (size_t i = 0; i < RenderableMeshEntitiesPublic.size(); i++)
		{
			RenderableMeshEntitiesPublic[i]->renderer->meshRenderData->shader->UseShader();
			RenderableMeshEntitiesPublic[i]->renderer->meshRenderData->shader->SetPointLights(m_PointLightList, m_PointLightCount, 4, 0);
		}
		for (size_t i = 0; i < RenderableModelEntitiesPublic.size(); i++)
		{
			RenderableModelEntitiesPublic[i]->renderer->modelRenderData->shader->UseShader();
			RenderableModelEntitiesPublic[i]->renderer->modelRenderData->shader->SetPointLights(m_PointLightList, m_PointLightCount, 4, 0);
		}
	}

	void Scene::SetSpotLights()
	{
		for (size_t i = 0; i < RenderableMeshEntitiesPublic.size(); i++)
		{
			RenderableMeshEntitiesPublic[i]->renderer->meshRenderData->shader->UseShader();
			RenderableMeshEntitiesPublic[i]->renderer->meshRenderData->shader->SetSpotLights(m_SpotLightList, m_SpotLightCount, 4 + m_PointLightCount, m_PointLightCount);
		}
		for (size_t i = 0; i < RenderableModelEntitiesPublic.size(); i++)
		{
			RenderableModelEntitiesPublic[i]->renderer->modelRenderData->shader->UseShader();
			RenderableModelEntitiesPublic[i]->renderer->modelRenderData->shader->SetSpotLights(m_SpotLightList, m_SpotLightCount, 4 + m_PointLightCount, m_PointLightCount);
		}
	}

	void Scene::RenderSceneShadowMap()
	{

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

	void Scene::RenderSceneOmniShadowMap()
	{
		if (!IsOmniShadowShaderSet())
		{
			LOG_CORE_WARN("Trying to render the omni shadow map, but the shadow shader isn't set!");
			return;
		}

		m_OmniShadowShader->UseShader();

		for (size_t i = 0; i < m_PointLightCount; i++)
		{
			if (m_PointLightList[i].GetShadowMap() == nullptr)
			{
				continue;
			}
			
			glViewport(0, 0, m_PointLightList[i].GetShadowMap()->GetShadowWidth(), m_PointLightList[i].GetShadowMap()->GetShadowHeight());
			m_PointLightList[i].GetShadowMap()->Write(); //Bind framebuffer
			glClear(GL_DEPTH_BUFFER_BIT);

			for (size_t j = 0; j < RenderableMeshEntitiesPublic.size(); j++)
			{
				RenderableMeshEntitiesPublic[j]->renderer->RenderToPointLightShadowMap(&m_PointLightList[i]);
			}
			for (size_t i = 0; i < RenderableModelEntitiesPublic.size(); i++)
			{
				RenderableModelEntitiesPublic[i]->renderer->RenderToPointLightShadowMap(&m_PointLightList[i]);
			}
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
		for (size_t i = 0; i < m_SpotLightCount; i++)
		{
			if (m_SpotLightList[i].GetShadowMap() == nullptr)
			{
				continue;
			}

			glViewport(0, 0, m_SpotLightList[i].GetShadowMap()->GetShadowWidth(), m_SpotLightList[i].GetShadowMap()->GetShadowHeight());
			m_SpotLightList[i].GetShadowMap()->Write();  //Bind framebuffer
			glClear(GL_DEPTH_BUFFER_BIT);

			for (size_t j = 0; j < RenderableMeshEntitiesPublic.size(); j++)
			{
				RenderableMeshEntitiesPublic[j]->renderer->RenderToPointLightShadowMap(&m_SpotLightList[i]);
			}
			for (size_t i = 0; i < RenderableModelEntitiesPublic.size(); i++)
			{
				RenderableModelEntitiesPublic[i]->renderer->RenderToPointLightShadowMap(&m_SpotLightList[i]);
			}
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}

	void Scene::setBackgroundColor(glm::vec3 colour)
	{
		m_BackgroundColour = colour;
	}

	void Scene::setSkybox(std::shared_ptr<Skybox> skybox)
	{
		m_Skybox = skybox;
	}

	void Scene::SetDirectionalLight(DirectionalLight* dLight)
	{
		m_DirectionalLight = dLight;
	}

	DirectionalLight* Scene::GetDirectionalLight()
	{
		return m_DirectionalLight;
	}

	int Scene::GetPointLightCount()
	{
		return m_PointLightCount;
	}

	int Scene::GetSpotLightCount()
	{
		return m_SpotLightCount;
	}

	bool Scene::IsOmniShadowShaderSet()
	{
		return m_OmniShadowShader != nullptr;
	}

	void Scene::useSkybox(bool useSkybox)
	{
		m_UseSkybox = useSkybox;
	}

	void Scene::setOmniShadowShader(Shader* omniShadowShader)
	{
		m_OmniShadowShader = omniShadowShader;
	}


	void Scene::setCamera(Camera* camera)
	{
		m_MainCamera = camera;
	}
	void Scene::updateObjects()
	{
		//for (size_t i = 0; i < m_RenderableObjectList.size(); i++)
		{
			//m_ObjectList[i]->Tick();
		}
	}

	void Scene::startObjects()
	{
		//for (size_t i = 0; i < m_RenderableObjectList.size(); i++)
		{
			//m_ObjectList[i]->Start();
		}
	}

	void Scene::addPointLight(const PointLight* pLight)
	{
		if (m_PointLightCount < MAX_POINT_LIGHTS)
		{
			m_PointLightList[m_PointLightCount] = *pLight;
			m_PointLightCount++;
		}
		else
		{
			printf("Error: Exceeded maximum point lights.\n");
		}
	}

	void Scene::addSpotLight(const SpotLight* sLight)
	{
		if (m_SpotLightCount < MAX_SPOT_LIGHTS)
		{
			m_SpotLightList[m_SpotLightCount] = *sLight;
			m_SpotLightCount++;
		}
		else
		{
			printf("Error: Exceeded maximum point lights.\n");
		}
	}
}