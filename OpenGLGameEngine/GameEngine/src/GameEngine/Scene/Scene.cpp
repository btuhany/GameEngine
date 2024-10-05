#include "Scene.h"
namespace GameEngine {
	Scene::Scene()
	{
		m_BackgroundColour = glm::vec3(0.0f, 0.0f, 0.0f);
		m_MainCamera = nullptr;
		m_DirectionalLight = nullptr;
		m_Skybox = nullptr;
		m_OmniShadowShader = nullptr;
	}

	Scene::~Scene()
	{
		printf("\n deleted scene \n");
		delete m_DirectionalLight;
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

	std::shared_ptr<Camera> Scene::GetCamera()
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

	void Scene::setOmniShadowShader(Shader* omniShadowShader)
	{
		m_OmniShadowShader = omniShadowShader;
	}


	void Scene::setCamera(std::shared_ptr<Camera> camera)
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

	void Scene::instantiateGameEntity(std::shared_ptr<GameEntity> entity, bool isActive)
	{
		m_gameEntities.push_back(entity);
		entity->HandleOnAfterInstantiated();
		entity->setActive(isActive);
	}

	void Scene::destroyGameEntity(std::shared_ptr<GameEntity> entity, bool disableFirst)
	{
		//TODO if entitiy references are contained in scene class, destroying will not affect it
		if (disableFirst)
		{
			entity->setActive(false);
		}
		auto it = std::find(m_gameEntities.begin(), m_gameEntities.end(), entity);
		if (it != m_gameEntities.end()) {
			entity->HandleOnPreDestroyed();
			m_gameEntities.erase(it);
		}
	}
}