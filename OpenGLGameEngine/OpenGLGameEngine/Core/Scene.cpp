#include "Scene.h"

Scene::Scene()
{
	m_BackgroundColour = glm::vec3(0.0f, 0.0f, 0.0f);
	m_UseSkybox = false;

}

Scene::~Scene()
{
	delete m_DirectionalLight;
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
	m_ObjectList.push_back(object);
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
	for (size_t i = 0; i < m_ObjectList.size(); i++)
	{
		m_ObjectList[i]->Render(projection, m_MainCamera->CalculateViewMatrix(), m_MainCamera, m_DirectionalLight);
	}
}

void Scene::SetPointLights()
{
	for (size_t x = 0; x < m_RenderShaders.size(); x++)
	{
		m_RenderShaders[x]->UseShader();
		m_RenderShaders[x]->SetPointLights(m_PointLightList, m_PointLightCount, 4, 0);
	}	
}

void Scene::SetSpotLights()
{
	for (size_t x = 0; x < m_RenderShaders.size(); x++)
	{
		m_RenderShaders[x]->UseShader();
		m_RenderShaders[x]->SetSpotLights(m_SpotLightList, m_SpotLightCount, 4 + m_PointLightCount, m_PointLightCount);
	}
}

void Scene::RenderSceneShadowMap()
{
	for (size_t i = 0; i < m_ObjectList.size(); i++)
	{
		m_ObjectList[i]->RenderShadowMap(m_DirectionalLight);
	}
}

void Scene::RenderSceneOmniShadowMap()
{
	m_OmniShadowShader->UseShader();

	for (size_t i = 0; i < m_PointLightCount; i++)
	{
		glViewport(0, 0, m_PointLightList[i].GetShadowMap()->GetShadowWidth(), m_PointLightList[i].GetShadowMap()->GetShadowHeight());
		m_PointLightList[i].GetShadowMap()->Write(); //Bind framebuffer
		glClear(GL_DEPTH_BUFFER_BIT);
		for (size_t j = 0; j < m_ObjectList.size(); j++)
		{
			m_ObjectList[j]->RenderOmniShadowMap(&m_PointLightList[i]);
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	for (size_t i = 0; i < m_SpotLightCount; i++)
	{
		glViewport(0, 0, m_SpotLightList[i].GetShadowMap()->GetShadowWidth(), m_SpotLightList[i].GetShadowMap()->GetShadowHeight());
		m_SpotLightList[i].GetShadowMap()->Write();  //Bind framebuffer
		glClear(GL_DEPTH_BUFFER_BIT);
		for (size_t j = 0; j < m_ObjectList.size(); j++)
		{
			m_ObjectList[j]->RenderOmniShadowMap(&m_SpotLightList[i]);
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

void Scene::setDirectionalLight(DirectionalLight* dLight)
{
	m_DirectionalLight = dLight;
}

DirectionalLight* Scene::getDirectionalLight()
{
	return m_DirectionalLight;
}

int Scene::GetPointLightCount()
{
	return m_PointLightCount;
}

void Scene::useSkybox(bool useSkybox)
{
	m_UseSkybox = useSkybox;
}

void Scene::registerRenderShader(Shader* shader)
{
	m_RenderShaders.push_back(shader);
}

void Scene::setCamera(Camera* camera)
{
	m_MainCamera = camera;
}
void Scene::updateObjects()
{
	for (size_t i = 0; i < m_ObjectList.size(); i++)
	{
		//m_ObjectList[i]->Tick();
	}
}

void Scene::startObjects()
{
	for (size_t i = 0; i < m_ObjectList.size(); i++)
	{
		//m_ObjectList[i]->Start();
	}
}

void Scene::AddPointLight(const PointLight* pLight)
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

void Scene::AddSpotLight(const SpotLight* sLight)
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