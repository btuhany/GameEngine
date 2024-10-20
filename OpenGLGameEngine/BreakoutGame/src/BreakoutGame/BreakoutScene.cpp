#include "BreakoutScene.h"

BreakoutScene::BreakoutScene() : Scene()
{
}

BreakoutScene::BreakoutScene(BreakoutSceneInputHandler* inputHandler) : Scene()
{
	m_InputHandler = inputHandler;
}

BreakoutScene::~BreakoutScene()
{
}

void BreakoutScene::Initialize()
{
	setCamera(std::make_shared<Camera>(glm::vec3(-10.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		0.0f, 0.0f, 5.0f, 0.1f, 60.0f, 0.1f, 400.0f, CAMERA_TYPE_ORTHOGONAL));

	LOG_INFO("Breakout scene initialized!");
	Scene::Initialize();
}

void BreakoutScene::Start()
{
}

void BreakoutScene::Update(GLfloat deltaTime)
{
}
