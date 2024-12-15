#include "DemoScene3D.h"


DemoScene3D::DemoScene3D() : Scene()
{
}

DemoScene3D::DemoScene3D(DemoSceneInputHandler* input) : Scene()
{
	m_InputReader = input;
	m_ObjectMoveSpeed = 5.0f;
	m_ObjectRotateSpeed = 2.0f;
	m_ObjectScaleSpeed = 0.05f;
}

DemoScene3D::~DemoScene3D()
{
}

void DemoScene3D::Initialize(float viewPortWidth, float viewPortHeight)
{
	Scene::Initialize(viewPortWidth, viewPortHeight);

	setCamera(std::make_shared<Camera>(glm::vec3(0.0f, 5.0f, 45.0f), 
		glm::vec3(0.0f, 1.0f, 0.0f), 
		-90.0f, 0.0f, 5.0f, 0.1f, 60.0f, 0.1f, 400.0f, CAMERA_TYPE_PERSPECTIVE));

	setBackgroundColor(glm::vec3(0.0f, 1.0f, 0.0f));
	initializeInputCallbacks();
	initializeShadowShaders();
	initializeSkybox();
	initializeGameObjects();
	initializeLights();

	LOG_INFO("Demo scene initialized!");
}

void DemoScene3D::Start()
{
	auto ironman = FindGameObject("ironMan");
	if (ironman == nullptr)
	{
		printf("Error! ironman is null");
	}
	auto m_HelicopterSmall = FindGameObject("helicopterSmall");
	if (m_HelicopterSmall == nullptr)
	{
		printf("Error! m_HelicopterSmall is null");
	}
	auto m_HelicopterBig = FindGameObject("helicopterBig");
	if (m_HelicopterBig == nullptr)
	{
		printf("Error! m_HelicopterBig is null");
	}


	ironman->transform->Scale(glm::vec3(0.1f, 0.1f, 0.1f));
	ironman->transform->Rotate(-60.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	ironman->transform->SetPosition(glm::vec3(20.0f, 1.0f, -10.0f));


	m_HelicopterSmall->transform->Rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	m_HelicopterSmall->transform->Rotate(180.0f, glm::vec3(0.0f, 1.0f, 0.0f));

	m_HelicopterBig->transform->Scale(glm::vec3(2.0f, 2.0f, 2.0f));
	m_HelicopterBig->transform->Rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	m_HelicopterBig->transform->Rotate(180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	m_HelicopterBig->transform->Translate(glm::vec3(-15.0f, -6.0f, -15.0f));
}

float smallHelicopterRotateYAxis = 0.0f;
float bigHelicopterRotateYAxis = 0.0f;
float ironmanPosIncreaseYAxis = 0.1f;
void DemoScene3D::Update(GLfloat deltaTime)
{
	m_DeltaTime = deltaTime;

	if (m_StopUpdate)
		return;

	auto ironman = FindGameObject("ironMan");
	if (ironman != nullptr)
	{
		if (ironman->transform->getPosition().y > 10)
		{
			ironmanPosIncreaseYAxis = -0.1f;
		}
		else if (ironman->transform->getPosition().y < -30)
		{
			ironmanPosIncreaseYAxis = 0.1f;
		}
		ironman->transform->Translate(glm::vec3(0.0f, ironmanPosIncreaseYAxis, 0.0f));
	}
	auto m_HelicopterSmall = FindGameObject("helicopterSmall");
	if (m_HelicopterSmall != nullptr)
	{
		smallHelicopterRotateYAxis = deltaTime * 12.5f;
		m_HelicopterSmall->transform->Rotate(smallHelicopterRotateYAxis, glm::vec3(0.0f, 1.0, 0.0f));
	}
	auto m_HelicopterBig = FindGameObject("helicopterBig");
	if (m_HelicopterBig != nullptr)
	{
		bigHelicopterRotateYAxis = deltaTime * -15.5f;
		m_HelicopterBig->transform->Rotate(bigHelicopterRotateYAxis, glm::vec3(0.0f, 1.0, 0.0f));
	}
}

std::shared_ptr<MeshData> DemoScene3D::createCubeMeshData()
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

std::shared_ptr<MeshData> DemoScene3D::createPlainMeshData()
{
	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-50.0f, -10.0f, -50.0f,	0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
		50.0f, -10.0f, -50.0f,	20.0f, 0.0f,  0.0f, 1.0f, 0.0f,
		-50.0f, -10.0f, 50.0f,	0.0f, 20.0f,  0.0f, 1.0f, 0.0f,
		50.0f, -10.0f, 50.0f,	20.0f, 20.0f,  0.0f, 1.0f, 0.0f
	};

	std::shared_ptr<MeshData> plainMesh = std::make_shared<MeshData>();
	plainMesh->CreateMesh(floorVertices, floorIndices, 32, 6);
	return plainMesh;
}

void DemoScene3D::initializeSkybox()
{
	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("src/DemoScene3D/Textures/skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("src/DemoScene3D/Textures/skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("src/DemoScene3D/Textures/skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("src/DemoScene3D/Textures/skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("src/DemoScene3D/Textures/skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("src/DemoScene3D/Textures/skybox/cupertin-lake_ft.tga");
	std::shared_ptr<Skybox> skybox = std::make_shared<Skybox>(skyboxFaces, "src/DemoScene3D/Shaders/skybox.vert", "src/DemoScene3D/Shaders/skybox.frag");
	setSkybox(skybox);
}

void DemoScene3D::initializeInputCallbacks()
{
	m_InputReader->OnPresssedRightEvent.AddHandler([this]() {handleOnRightKey();});
	m_InputReader->OnPresssedLeftEvent.AddHandler([this]() {handleOnLeftKey();});
	m_InputReader->OnPresssedUpEvent.AddHandler([this]() {handleOnUpKey();});
	m_InputReader->OnPresssedDownEvent.AddHandler([this]() {handleOnDownKey();});
	m_InputReader->OnShiftKeyEvent.AddHandler([this](int keyState) {handleOnShiftKey(keyState);});
	m_InputReader->OnPressedSpaceEvent.AddHandler([this]() {handleOnSpaceKey(); });
	m_InputReader->OnPressedCtrlEvent.AddHandler([this]() {handleOnCtrlKey(); });
	m_InputReader->OnEnableDisableKeyEvent.AddHandler([this]() {handleOnEnableDisableKey(); });
	m_InputReader->OnDestroyKeyEvent.AddHandler([this]() {handleOnDestroyObjectKey(); });
	m_InputReader->OnPressedRotateLeftKeyEvent.AddHandler([this]() {handleOnRotateLeftKey(); });
	m_InputReader->OnPressedRotateRightKeyEvent.AddHandler([this]() {handleOnRotateRightKey(); });
	m_InputReader->OnPauseKeyEvent.AddHandler([this]() {handleOnPauseKey(); });
	m_InputReader->OnShaderChangeKeyEvent.AddHandler([this]() {handleOnShaderChangeKey(); });
	m_InputReader->OnSelectLeftObjectKeyEvent.AddHandler([this]() {handleOnSelectLeftObjectKey(); });
	m_InputReader->OnSelectRightObjectKeyEvent.AddHandler([this]() {handleOnSelectRightObjectKey(); });
	m_InputReader->OnScaleUpKeyEvent.AddHandler([this]() {handleOnScaleUpKey(); });
	m_InputReader->OnScaleDownKeyEvent.AddHandler([this]() {handleOnScaleDownKey(); });
}

void DemoScene3D::initializeGameObjects()
{
	static const char* vShaderLocation = "src/DemoScene3D/Shaders/shader.vert";
	static const char* fShaderLocation = "src/DemoScene3D/Shaders/shader.frag";
	static const char* fNormalShaderLocation = "src/DemoScene3D/Shaders/normalRenderShader.frag";

	m_MainRenderShader = std::make_shared<Shader>();
	m_MainRenderShader->CreateFromFiles(vShaderLocation, fShaderLocation);
	m_MainRenderShader->SetUseDirLightShadow(true); //TODO

	m_NormalRenderShader = std::make_shared<Shader>();
	m_NormalRenderShader->CreateFromFiles(vShaderLocation, fNormalShaderLocation);

	std::shared_ptr<Material> shinyMaterial = std::make_shared<Material>(590.0f, 475.5f);
	std::shared_ptr<Material> roughMaterial = std::make_shared<Material>(0.1f, 3.0f);

	std::shared_ptr<Texture> spidermanTexture = std::make_shared<Texture>("src/DemoScene3D/Textures/spiderman.png");
	spidermanTexture->LoadTextureWithAlpha();
	std::shared_ptr<Texture> plainTexture = std::make_shared<Texture>("src/DemoScene3D/Textures/plain.png");
	plainTexture->LoadTextureWithAlpha();

	std::shared_ptr<ModelData> helicopterModelDataNew = std::make_shared<ModelData>();
	helicopterModelDataNew->LoadModel("src/DemoScene3D/Models/uh60.obj");
	std::shared_ptr<ModelData> ironmanModelData = std::make_shared<ModelData>();
	ironmanModelData->LoadModel("src/DemoScene3D/Models/IronMan.obj");

	std::shared_ptr<ModelRenderData> ironmanRenderData = std::make_shared<ModelRenderData>(ironmanModelData, nullptr, shinyMaterial, m_MainRenderShader);
	std::shared_ptr<ModelRenderData> helicopterRenderData = std::make_shared<ModelRenderData>(helicopterModelDataNew, nullptr, shinyMaterial, m_MainRenderShader);

	std::shared_ptr<MeshRenderData> meshRenderData = std::make_shared<MeshRenderData>(createCubeMeshData(), spidermanTexture, shinyMaterial, m_MainRenderShader);
	std::shared_ptr<MeshRenderData> plainRenderData = std::make_shared<MeshRenderData>(createPlainMeshData(), spidermanTexture, roughMaterial, m_MainRenderShader);


	auto m_HelicopterBig = std::make_shared<ModelEntity>(helicopterRenderData);
	auto m_HelicopterSmall = std::make_shared<ModelEntity>(helicopterRenderData);
	auto ironman = std::make_shared<ModelEntity>(ironmanRenderData);

	m_HelicopterBig->setName("helicopterBig");
	instantiateGameEntity(m_HelicopterBig);
	m_HelicopterSmall->setName("helicopterSmall");
	instantiateGameEntity(m_HelicopterSmall);
	ironman->setName("ironMan");
	instantiateGameEntity(ironman);


	std::shared_ptr<MeshEntity> cubeMeshEntity = std::make_shared<MeshEntity>(meshRenderData);
	cubeMeshEntity->GetComponent<Transform>()->Translate(glm::vec3(36.0f, -7.0f, -12.0f));
	cubeMeshEntity->transform->Scale(glm::vec3(3.0f, 3.0f, 1.5f));
	cubeMeshEntity->setName("spiderManUglyCube");
	instantiateGameEntity(cubeMeshEntity);

	std::shared_ptr<MeshEntity> spidermanPlainEntity = std::make_shared<MeshEntity>(plainRenderData);
	spidermanPlainEntity->GetComponent<Transform>()->SetPosition(glm::vec3(0.0f, -10.0f, 0.0f));
	spidermanPlainEntity->transform->Scale(glm::vec3(1.0f, 1.0f, 1.0f));
	spidermanPlainEntity->setName("spiderManPlain");
	instantiateGameEntity(spidermanPlainEntity);

	std::shared_ptr<MeshEntity> spidermanCubeEntity = std::make_shared<MeshEntity>(meshRenderData);
	spidermanCubeEntity->transform->Translate(glm::vec3(15.0f, 10.0f, 15.0f));
	spidermanCubeEntity->transform->Scale(glm::vec3(3.0f, 3.0f, 3.0f));
	spidermanCubeEntity->setName("spiderManCube");
	instantiateGameEntity(spidermanCubeEntity);
}

void DemoScene3D::initializeShadowShaders()
{
	std::shared_ptr<Shader> directionalShadowShader = std::make_shared<Shader>();
	directionalShadowShader->CreateFromFiles("src/DemoScene3D/Shaders/directional_shadow_map.vert", "src/DemoScene3D/Shaders/directional_shadow_map.frag");
	setDirectionalLightShadowShader(directionalShadowShader);

	std::shared_ptr<Shader> omniShadowShader = std::make_shared<Shader>();
	omniShadowShader->CreateFromFiles("src/DemoScene3D/Shaders/omni_shadow_map.vert", "src/DemoScene3D/Shaders/omni_shadow_map.geom", "src/DemoScene3D/Shaders/omni_shadow_map.frag");
	setOmniShadowShader(omniShadowShader);
}

void DemoScene3D::initializeLights()
{
	std::shared_ptr<DirectionalLight> dirLight = std::make_shared<DirectionalLight>(0.0f, 0.02f,
		0.2f, 0.5f, 1.0f,
		0.4f, -0.8f, 0.01f, 1024, 1024);
	setDirectionalLight(dirLight);

	addPointLight(new PointLight(0.0f, 500.5f,
		0.3f, 0.7f, 0.0f,
		7.0f, 15.0f, 5.0f,
		0.03f, 1.0f, 1.0f,
		2048, 2048,
		0.01f, 100.0f));
	addPointLight(new PointLight(0.0f, 255.5f,
		1.0f, 0.0f, 1.0f,
		15.0f, 35.0f, 30.0f,
		0.5f, 0.1f, 0.3f,
		1024, 1024,
		0.01f, 300.0f));
	addSpotLight(new SpotLight(0.0f, 80.5f,
		1.0f, 0.0f, 0.0f,
		0.0f, 20.0f, 0.0f,
		0.0f, -1.0f, 0.6f,
		1.1f, 1.0f, 0.01f,
		60.0f,
		720, 720,
		0.01f, 100.0f));
	addSpotLight(new SpotLight(0.0f, 155.0f,
		0.0f, 0.5f, 1.0f,
		0.0f, -10.0f, 0.0f,
		0.0f, 0.5f, 0.0f,
		0.1f, 0.1f, 0.1f,
		100.0f,
		0.01f, 200.0f));
	addSpotLight(new SpotLight(0.0f, 100.0f,
		0.0f, 1.0f, 1.0f,
		-7.0f, 12.0f, 8.0f,
		0.7f, -0.6f, 0.3f,
		0.8f, 0.01f, 0.8f,
		100.0f,
		1024, 1024,
		0.01f, 200.0f));
}

void DemoScene3D::handleOnRightKey()
{
	//getCamera()->MoveRight(m_CameraSpeed * m_DeltaTime);
	if (m_CurrentObjectIndex == -1)
		return;

	auto pos = m_GameEntities[m_CurrentObjectIndex]->transform->getPosition();
	m_GameEntities[m_CurrentObjectIndex]->transform->Translate(glm::vec3(m_ObjectMoveSpeed * m_DeltaTime, 0.0f, 0.0f));
}

void DemoScene3D::handleOnLeftKey()
{
	if (m_CurrentObjectIndex == -1)
		return;
	//getCamera()->MoveLeft(m_CameraSpeed * m_DeltaTime);
	auto pos = m_GameEntities[m_CurrentObjectIndex]->transform->getPosition();
	m_GameEntities[m_CurrentObjectIndex]->transform->Translate(glm::vec3(-(m_ObjectMoveSpeed * m_DeltaTime), 0.0f, 0.0f));
}

void DemoScene3D::handleOnUpKey()
{
	if (m_CurrentObjectIndex == -1)
		return;
	//getCamera()->MoveForward(m_CameraSpeed * m_DeltaTime);
	auto pos = m_GameEntities[m_CurrentObjectIndex]->transform->getPosition();
	m_GameEntities[m_CurrentObjectIndex]->transform->Translate(glm::vec3(0.0f, 0.0f, -(m_ObjectMoveSpeed * m_DeltaTime)));
}

void DemoScene3D::handleOnDownKey()
{
	if (m_CurrentObjectIndex == -1)
		return;
	//getCamera()->MoveBack(m_CameraSpeed * m_DeltaTime);
	auto pos = m_GameEntities[m_CurrentObjectIndex]->transform->getPosition();
	m_GameEntities[m_CurrentObjectIndex]->transform->Translate(glm::vec3(0.0f, 0.0f, (m_ObjectMoveSpeed * m_DeltaTime)));
}

void DemoScene3D::handleOnShiftKey(int keyState)
{
	if (keyState == KEY_STATE_PRESS)
	{
		m_ObjectMoveSpeed = 15.0f;
		m_ObjectRotateSpeed = 5.0f;
	}
	else if (keyState == KEY_STATE_RELEASE)
	{
		m_ObjectMoveSpeed = 5.0f;
		m_ObjectRotateSpeed = 2.0f;
	}
}


void DemoScene3D::handleOnSpaceKey()
{
	if (m_CurrentObjectIndex == -1)
		return;
	m_GameEntities[m_CurrentObjectIndex]->transform->Translate(glm::vec3(0.0f, m_ObjectMoveSpeed * 0.05f, 0.0f));
}

void DemoScene3D::handleOnCtrlKey()
{
	if (m_CurrentObjectIndex == -1)
		return;
	m_GameEntities[m_CurrentObjectIndex]->transform->Translate(glm::vec3(0.0f, -m_ObjectMoveSpeed * 0.05f, 0.0f));
}

void DemoScene3D::handleOnEnableDisableKey()
{
	if (m_CurrentObjectIndex == -1)
		return;
	m_GameEntities[m_CurrentObjectIndex]->setActive(!m_GameEntities[m_CurrentObjectIndex]->IsActive());
}

void DemoScene3D::handleOnDestroyObjectKey()
{
	if (m_CurrentObjectIndex == -1)
		return;
	destroyGameEntity(m_GameEntities[m_CurrentObjectIndex], false);
}

void DemoScene3D::handleOnRotateLeftKey()
{
	if (m_CurrentObjectIndex == -1)
		return;
	m_GameEntities[m_CurrentObjectIndex]->transform->Rotate(-m_ObjectRotateSpeed, glm::vec3(0.0f, 1.0f, 0.0f));
}

void DemoScene3D::handleOnRotateRightKey()
{
	if (m_CurrentObjectIndex == -1)
		return;
	m_GameEntities[m_CurrentObjectIndex]->transform->Rotate(m_ObjectRotateSpeed, glm::vec3(0.0f, 1.0f, 0.0f));
}

void DemoScene3D::handleOnPauseKey()
{
	m_StopUpdate = !m_StopUpdate;
}

bool isOnMainRenderer = false;
void DemoScene3D::handleOnShaderChangeKey()
{
	for (size_t i = 0; i < m_GameEntities.size(); i++)
	{
		auto currentObject = m_GameEntities[i];
		auto rendererComponent = currentObject->GetComponentOfBaseType<RendererComponent>();
		if (rendererComponent != nullptr)
		{
			if (isOnMainRenderer)
			{
				rendererComponent->ChangeRenderShader(m_NormalRenderShader);
			}
			else
			{
				rendererComponent->ChangeRenderShader(m_MainRenderShader);
			}
		}
	}
	isOnMainRenderer = !isOnMainRenderer;
}

void DemoScene3D::handleOnSelectRightObjectKey()
{
	for (size_t i = 0; i < m_GameEntities.size(); i++)
	{
		auto currentObject = m_GameEntities[i];
		auto rendererComponent = currentObject->GetComponentOfBaseType<RendererComponent>();
		if (rendererComponent != nullptr)
		{
			rendererComponent->ChangeRenderShader(m_MainRenderShader);
		}
	}

	m_CurrentObjectIndex++;
	if (m_CurrentObjectIndex >= m_GameEntities.size())
	{
		m_CurrentObjectIndex = 0;
	}
	auto currentObject = m_GameEntities[m_CurrentObjectIndex];

	auto rendererComponent = currentObject->GetComponentOfBaseType<RendererComponent>();
	if (rendererComponent != nullptr)
		rendererComponent->ChangeRenderShader(m_NormalRenderShader);
}

void DemoScene3D::handleOnSelectLeftObjectKey()
{
	for (size_t i = 0; i < m_GameEntities.size(); i++)
	{
		auto currentObject = m_GameEntities[i];
		auto rendererComponent = currentObject->GetComponentOfBaseType<RendererComponent>();
		if (rendererComponent != nullptr)
		{
			rendererComponent->ChangeRenderShader(m_MainRenderShader);
		}
	}

	m_CurrentObjectIndex--;
	if (m_CurrentObjectIndex < 0)
	{
		m_CurrentObjectIndex = m_GameEntities.size() - 1;
	}
	auto currentObject = m_GameEntities[m_CurrentObjectIndex];
	auto rendererComponent = currentObject->GetComponentOfBaseType<RendererComponent>();
	if (rendererComponent != nullptr)
		rendererComponent->ChangeRenderShader(m_NormalRenderShader);
}

void DemoScene3D::handleOnScaleUpKey()
{
	if (m_CurrentObjectIndex == -1)
		return;
	auto gameObjTransform = m_GameEntities[m_CurrentObjectIndex]->transform;
	auto gameObjScale = gameObjTransform->getScale();
	gameObjTransform->Scale(gameObjScale + glm::vec3(m_ObjectScaleSpeed));
}

void DemoScene3D::handleOnScaleDownKey()
{
	if (m_CurrentObjectIndex == -1)
		return;
	auto gameObjTransform = m_GameEntities[m_CurrentObjectIndex]->transform;
	auto gameObjScale = gameObjTransform->getScale();
	gameObjTransform->Scale(gameObjScale - glm::vec3(m_ObjectScaleSpeed));
}

