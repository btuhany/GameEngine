#include "Scene.h"
namespace GameEngine {
	Scene::Scene()
	{
		m_BackgroundColour = glm::vec3(0.0f, 0.0f, 0.0f);
		m_MainCamera = nullptr;
		m_DirectionalLight = nullptr;
		m_Skybox = nullptr;
		m_OmniShadowShader = nullptr;
		m_IsSceneEnd = false;
	}

	Scene::~Scene()
	{
	}

	void Scene::Initialize(float viewPortWidth, float viewPortHeight)
	{
		m_IsInitialized = true;
	}

	void Scene::Start()
	{
	}

	void Scene::Update(GLfloat deltaTime)
	{

	}

	std::shared_ptr<Camera> Scene::getCamera()
	{
		return m_MainCamera;
	}

	std::shared_ptr<Skybox> Scene::getSkybox()
	{
		return m_Skybox;
	}

	glm::vec3 Scene::getBackgroundColor()
	{
		return m_BackgroundColour;
	}

	void Scene::setBackgroundColor(glm::vec3 colour)
	{
		m_BackgroundColour = colour;
	}

	bool Scene::getIsSceneEnd()
	{
		return m_IsSceneEnd;
	}

	void Scene::setSkybox(std::shared_ptr<Skybox> skybox)
	{
		m_Skybox = skybox;
	}

	void Scene::setDirectionalLight(std::shared_ptr<DirectionalLight> dLight)
	{
		m_DirectionalLight = dLight;
	}

	std::shared_ptr<DirectionalLight> Scene::getDirectionalLight()
	{
		return m_DirectionalLight;
	}

	int Scene::getPointLightCount()
	{
		return m_PointLightCount;
	}

	int Scene::getSpotLightCount()
	{
		return m_SpotLightCount;
	}

	std::shared_ptr<Shader> Scene::getOmniShadowShader()
	{
		return m_OmniShadowShader;
	}

	std::shared_ptr<Shader> Scene::getDirectionalLightShadowShader()
	{
		return m_DirLightShadowShader;
	}

	void Scene::setDirectionalLightShadowShader(std::shared_ptr<Shader>  dirShadowShader)
	{
		m_DirLightShadowShader = dirShadowShader;
	}

	bool Scene::IsOmniShadowShaderSet()
	{
		return m_OmniShadowShader != nullptr;
	}

	bool Scene::IsInitialized()
	{
		return m_IsInitialized;
	}

	std::shared_ptr<GameEntity> Scene::FindGameObject(std::string name)
	{
		for (size_t i = 0; i < m_GameEntities.size(); i++)
		{
			auto gameObj = m_GameEntities[i];
			if (gameObj->getName() == name)
			{
				return gameObj;
			}
		}
		return nullptr;
	}

	void Scene::setOmniShadowShader(std::shared_ptr<Shader> omniShadowShader)
	{
		m_OmniShadowShader = omniShadowShader;
	}


	void Scene::setCamera(std::shared_ptr<Camera> camera)
	{
		if (m_MainCamera != nullptr)
		{
			auto sceneCameraChangedEventData = std::make_shared<SceneCameraChangedEvent>();
			sceneCameraChangedEventData->camera = camera;
			EventManager::GetInstance().Publish(sceneCameraChangedEventData);
		}
		m_MainCamera = camera;
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
		m_GameEntities.push_back(entity);
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
		auto it = std::find(m_GameEntities.begin(), m_GameEntities.end(), entity);
		if (it != m_GameEntities.end()) {
			entity->HandleOnPreDestroyed();
			m_GameEntities.erase(it);
		}
	}
	void Scene::setIsSceneEnd(bool value)
	{
		m_IsSceneEnd = value;
	}
}