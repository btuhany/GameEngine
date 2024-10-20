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
		glm::vec3(0.0f, 0.0f, -5.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		0.0f, 0.0f, 5.0f, 0.1f, 30, 0.1f, 100.0f, CAMERA_TYPE_ORTHOGONAL));


	static const char* vShaderLocation = "src/BreakoutGame/Shaders/shader.vert";
	static const char* fShaderLocation = "src/BreakoutGame/Shaders/shader.frag";

	std::shared_ptr<Shader> mainShader = std::make_shared<Shader>();
	mainShader->CreateFromFiles(vShaderLocation, fShaderLocation);

	std::shared_ptr<Material> shinyMaterial = std::make_shared<Material>(590.0f, 475.5f);
	std::shared_ptr<Texture> spidermanTexture = std::make_shared<Texture>("src/BreakoutGame/Textures/spiderman.png");
	spidermanTexture->LoadTextureWithAlpha();


	std::shared_ptr<MeshRenderData> meshRenderData = std::make_shared<MeshRenderData>(createCubeMeshData(), spidermanTexture, shinyMaterial, mainShader);

	std::shared_ptr<MeshEntity> cubeMeshEntity = std::make_shared<MeshEntity>(meshRenderData);
	cubeMeshEntity->setName("spiderManUglyCube");
	cubeMeshEntity->transform->SetPosition(glm::vec3(5.0f, 5.0f, 5.0f));
	instantiateGameEntity(cubeMeshEntity);

	std::shared_ptr<MeshEntity> cubeMeshEntity2 = std::make_shared<MeshEntity>(meshRenderData);
	cubeMeshEntity2->setName("spiderManUglyCube");
	cubeMeshEntity2->transform->SetPosition(glm::vec3(0.0, 0.0f, 0.0f));
	instantiateGameEntity(cubeMeshEntity2);


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
		-1.0f, -1.0f, 1.0f, 	1.0f, 0.0f,		-1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,		0.0f, 0.0f,		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,		0.0f, 1.0f,		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, 1.0f,	1.0f, 1.0f,		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,		1.0f, 0.0f,		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,		0.0f, 0.0f,		1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,		1.0f, 0.0f,		-1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,		0.0f, 0.0f,		-1.0f, 1.0f, 1.0f
	};

	unsigned int indices[] = {
	2, 0, 1,
	3, 0, 2,
	4, 2, 5,
	3, 2, 4,
	7, 3, 4,
	0, 3, 7,
	1, 0, 6,
	6, 0, 7,
	1, 6, 2,
	2, 6, 5,
	4, 5, 6,
	4, 6, 7
	};

	std::shared_ptr<MeshData> cubeMesh = std::make_shared<MeshData>();
	cubeMesh->CreateMesh(vertices, indices, 64, 36);
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
		setCamera(std::make_shared<Camera>(
			glm::vec3(0.0f, 0.0f, -5.0f),
			glm::vec3(0.0f, 1.0f, 0.0f),
			0.0f, 0.0f, 5.0f, 0.1f, 30.0f, 0.1f, 100.0f, CAMERA_TYPE_ORTHOGONAL));
	}
	else if (getCamera()->getCameraType() == CAMERA_TYPE_ORTHOGONAL)
	{
		setCamera(std::make_shared<Camera>(
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f),
			0.0f, 0.0f, 5.0f, 0.1f, 60.0f, 0.1f, 100.0f, CAMERA_TYPE_PERSPECTIVE));
	}
}
