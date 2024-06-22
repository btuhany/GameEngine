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
		delete m_Skybox;


		for (auto obj : m_RenderableObjectList) {
			obj->ClearRenderableObject();
		}
		m_RenderableObjectList.clear();
		Renderer::ClearRenderers();
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

	void Scene::AddObject(RenderableObject* object)
	{
		m_RenderableObjectList.push_back(object);
	}

	Camera* Scene::GetCamera()
	{
		return m_MainCamera;
	}

	Skybox* Scene::GetSkybox()
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
		for (size_t i = 0; i < m_RenderableObjectList.size(); i++)
		{
			m_RenderableObjectList[i]->GetRenderShader()->UseShader();
			m_RenderableObjectList[i]->Render(projection, m_MainCamera->CalculateViewMatrix(), m_MainCamera, m_DirectionalLight);
		}
	}

	void Scene::SetPointLights()
	{
		for (size_t i = 0; i < m_RenderableObjectList.size(); i++)
		{
			m_RenderableObjectList[i]->GetRenderShader()->UseShader();
			m_RenderableObjectList[i]->GetRenderShader()->SetPointLights(m_PointLightList, m_PointLightCount, 4, 0);
		}
	}

	void Scene::SetSpotLights()
	{
		for (size_t x = 0; x < m_RenderableObjectList.size(); x++)
		{
			m_RenderableObjectList[x]->GetRenderShader()->UseShader();
			m_RenderableObjectList[x]->GetRenderShader()->SetSpotLights(m_SpotLightList, m_SpotLightCount, 4 + m_PointLightCount, m_PointLightCount);
		}
	}

	void Scene::RenderSceneShadowMap()
	{
		for (size_t i = 0; i < m_RenderableObjectList.size(); i++)
		{
			m_RenderableObjectList[i]->RenderShadowMap(m_DirectionalLight);
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Scene::RenderSceneOmniShadowMap()
	{
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
			for (size_t j = 0; j < m_RenderableObjectList.size(); j++)
			{
				m_RenderableObjectList[j]->RenderOmniShadowMap(&m_PointLightList[i]);
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
			for (size_t j = 0; j < m_RenderableObjectList.size(); j++)
			{
				m_RenderableObjectList[j]->RenderOmniShadowMap(&m_SpotLightList[i]);
			}
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}

	void Scene::setBackgroundColor(glm::vec3 colour)
	{
		m_BackgroundColour = colour;
	}

	void Scene::setSkybox(Skybox* skybox)
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
		for (size_t i = 0; i < m_RenderableObjectList.size(); i++)
		{
			//m_ObjectList[i]->Tick();
		}
	}

	void Scene::startObjects()
	{
		for (size_t i = 0; i < m_RenderableObjectList.size(); i++)
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