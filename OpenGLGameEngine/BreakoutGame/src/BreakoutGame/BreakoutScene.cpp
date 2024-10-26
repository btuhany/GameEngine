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
	initializeInputCallbacks();
	setCamera(std::make_shared<Camera>(
		glm::vec3(0.0f, 0.0f, 10.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		-90.0f, 0.0f, 5.0f, 0.1f, 60, 0.1f, 100.0f, CAMERA_TYPE_PERSPECTIVE));
	
	static const char* vShaderLocation = "src/BreakoutGame/Shaders/shader.vert";
	static const char* fShaderLocation = "src/BreakoutGame/Shaders/shader.frag";

	std::shared_ptr<Shader> mainShader = std::make_shared<Shader>();
	mainShader->CreateFromFiles(vShaderLocation, fShaderLocation);

	std::shared_ptr<Material> shinyMaterial = std::make_shared<Material>(590.0f, 475.5f);
	std::shared_ptr<Texture> spidermanTexture = std::make_shared<Texture>("src/BreakoutGame/Textures/spiderman.png");
	spidermanTexture->LoadTextureWithAlpha();


	std::shared_ptr<SpriteRenderData> spriteRenderData = std::make_shared<SpriteRenderData>(spidermanTexture, shinyMaterial, mainShader);

	std::shared_ptr<SpriteEntity> quadEntity = std::make_shared<SpriteEntity>(spriteRenderData);
	quadEntity->setName("spiderManUglyQuad2");
	quadEntity->transform->SetPosition(glm::vec3(5.0f, 5.0f, -5.0f));
	instantiateGameEntity(quadEntity);

	std::shared_ptr<SpriteEntity> spriteEntity = std::make_shared<SpriteEntity>(spriteRenderData);
	spriteEntity->setName("spiderManUglyQuad1");
	spriteEntity->transform->SetPosition(glm::vec3(0.0, 0.0f, 0.0f));
	instantiateGameEntity(spriteEntity);


	LOG_INFO("Breakout scene initialized!");
	Scene::Initialize();
}

void BreakoutScene::Start()
{
}

void BreakoutScene::Update(GLfloat deltaTime)
{
}

std::shared_ptr<MeshData> BreakoutScene::createCubeMeshData()
{
	GLfloat vertices[] =
	{
		//x      y     z		 u     y			normals
		-1.0f, -1.0f, 0.0f, 	0.0f, 1.0f,		0.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 0.0f,	1.0f, 1.0f,		0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 1.0f,
		-1.0f, 1.0f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 1.0f
	};

	unsigned int indices[] = {
		0,1,2,
		2,3,0
	};

	std::shared_ptr<MeshData> cubeMesh = std::make_shared<MeshData>();
	cubeMesh->CreateMesh(vertices, indices, 32, 6);
	return cubeMesh;
}

void BreakoutScene::initializeInputCallbacks()
{
	m_InputHandler->OnPressedCameraTypeChangeKeyEvent.AddHandler(
		[this]() {
			changeCameraType();
		});
}


void BreakoutScene::changeCameraType()
{
	if (getCamera()->getCameraType() == CAMERA_TYPE_PERSPECTIVE)
	{
		auto pos = getCamera()->getPosition();
		auto yaw = getCamera()->getYawValue();
		auto pitch = getCamera()->getPitchValue();
		setCamera(std::make_shared<Camera>(
			pos,
			glm::vec3(0.0f, 1.0f, 0.0f),
			yaw, pitch, 5.0f, 0.1f, 30.0f, 0.1f, 100.0f, CAMERA_TYPE_ORTHOGONAL));
	}
	else if (getCamera()->getCameraType() == CAMERA_TYPE_ORTHOGONAL)
	{
		auto pos = getCamera()->getPosition();
		auto yaw = getCamera()->getYawValue();
		auto pitch = getCamera()->getPitchValue();
		setCamera(std::make_shared<Camera>(
			pos,
			glm::vec3(0.0f, 1.0f, 0.0f),
			yaw, pitch, 5.0f, 0.1f, 60.0f, 0.1f, 100.0f, CAMERA_TYPE_PERSPECTIVE));
	}
}
