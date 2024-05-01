#include "Scene.h"

Scene::Scene()
{
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

void Scene::AddObject(Object* object)
{
	m_ObjectList.push_back(object);
}

Camera* Scene::GetCamera()
{
	return &m_MainCamera;
}

void Scene::renderScene(glm::mat4 projection)
{
	for (size_t i = 0; i < m_ObjectList.size(); i++)
	{
		m_ObjectList[i]->RenderUpdate(projection, m_MainCamera.CalculateViewMatrix(), &m_MainCamera);
	}
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

void Scene::setCamera(Camera camera)
{
	m_MainCamera = camera;
}