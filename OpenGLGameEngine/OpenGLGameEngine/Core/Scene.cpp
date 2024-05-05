#include "Scene.h"

Scene::Scene()
{
	m_BackgroundColour = glm::vec3(0.0f, 0.0f, 0.0f);
	m_UseSkybox = false;
}

Scene::~Scene()
{
}

void Scene::Initialize()
{
}

void Scene::Start()
{
}

void Scene::Update(glm::mat4 projection, GLfloat deltaTime)
{
	renderScene(projection);
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

void Scene::renderScene(glm::mat4 projection)
{
	for (size_t i = 0; i < m_ObjectList.size(); i++)
	{
		m_ObjectList[i]->Render(projection, m_MainCamera->CalculateViewMatrix(), m_MainCamera);
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

void Scene::useSkybox(bool useSkybox)
{
	m_UseSkybox = useSkybox;
}

void Scene::setCamera(Camera* camera)
{
	m_MainCamera = camera;
}
void Scene::updateObjects()
{
	for (size_t i = 0; i < m_ObjectList.size(); i++)
	{
		m_ObjectList[i]->Tick();
	}
}

void Scene::startObjects()
{
	for (size_t i = 0; i < m_ObjectList.size(); i++)
	{
		m_ObjectList[i]->Start();
	}
}
