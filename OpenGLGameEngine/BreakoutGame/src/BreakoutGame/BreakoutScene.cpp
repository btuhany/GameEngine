#include "BreakoutScene.h"

BreakoutScene::BreakoutScene() : Scene()
{
}

BreakoutScene::~BreakoutScene()
{
}

void BreakoutScene::Initialize()
{
	//LOG_INFO("Breakout scene initialized!");
	//static const char* vShaderLocation = "src/BreakoutGame/Shaders/shader.vert";
	//static const char* fShaderLocation = "src/BreakoutGame/Shaders/shader.frag";
	//Shader* rendererShader = new Shader();
	//rendererShader->CreateFromFiles2D(vShaderLocation, fShaderLocation);

	setCamera(new Camera(glm::vec3(-10.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f, 5.0f, 0.1f, 60.0f, 0.1f, 100.0f, CAMERA_TYPE_ORTHOGONAL));
	//setBackgroundColor(glm::vec3(0.0f, 1.0f, 0.0f));

	//SetDirectionalLight(new DirectionalLight(0.0f, 0.15f,
	//	0.0f, 0.5f, 1.0f,
	//	0.4f, -0.8f, 0.01f, 1024, 1024));
}

void BreakoutScene::Start()
{
}

void BreakoutScene::Update(GLfloat deltaTime)
{
}
