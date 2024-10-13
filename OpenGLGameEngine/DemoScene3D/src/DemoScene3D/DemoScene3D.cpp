#include "DemoScene3D.h"


DemoScene3D::DemoScene3D() : Scene()
{
}

DemoScene3D::DemoScene3D(DemoSceneInputHandler* input) : Scene()
{
	m_InputReader = input;
}

DemoScene3D::~DemoScene3D()
{
	printf("deleted demoscnee");
}

void DemoScene3D::Initialize()
{
	Scene::Initialize();
	LOG_INFO("Demo scene initialized!");

	m_InputReader->OnPresssedRightEvent.AddHandler([this]() {handleOnRightKey();});
	m_InputReader->OnPresssedDownEvent.AddHandler([this]() {handleOnDownKey();});
	m_InputReader->OnPresssedLeftEvent.AddHandler([this]() {handleOnLeftKey();});
	m_InputReader->OnPresssedUpEvent.AddHandler([this]() {handleOnUpKey();});
	m_InputReader->OnPressedShiftEvent.AddHandler([this]() {handleOnShiftKey();});
	m_InputReader->OnReleasedShiftEvent.AddHandler([this]() {handleOnShiftReleasedKey();});
	m_InputReader->OnPressedSpaceEvent.AddHandler([this]() {handleOnSpaceKey(); });
	static const char* vShaderLocation = "src/DemoScene3D/Shaders/shader.vert";
	static const char* fShaderLocation = "src/DemoScene3D/Shaders/shader.frag";
	std::shared_ptr<Shader> rendererShader = std::make_shared<Shader>();
	rendererShader->CreateFromFiles(vShaderLocation, fShaderLocation);
	rendererShader->SetUseDirLightShadow(true); //TODO
	std::shared_ptr<Shader> rendererShader2 = std::make_shared<Shader>();
	rendererShader2->CreateFromFiles(vShaderLocation, fShaderLocation);

	std::shared_ptr<Shader> directionalShadowShader = std::make_shared<Shader>();
	directionalShadowShader->CreateFromFiles("src/DemoScene3D/Shaders/directional_shadow_map.vert", "src/DemoScene3D/Shaders/directional_shadow_map.frag");
	setDirectionalLightShadowShader(directionalShadowShader);


	std::shared_ptr<Shader> omniShadowShader = std::make_shared<Shader>();
	omniShadowShader->CreateFromFiles("src/DemoScene3D/Shaders/omni_shadow_map.vert", "src/DemoScene3D/Shaders/omni_shadow_map.geom", "src/DemoScene3D/Shaders/omni_shadow_map.frag");
	setOmniShadowShader(omniShadowShader);
	LOG_INFO("Demo scene initialized2!");
	DirectionalLight* dirLight = new DirectionalLight(0.0f, 0.02f,
		0.2f, 0.5f, 1.0f,
		0.4f, -0.8f, 0.01f, 1024, 1024);
	setDirectionalLight(dirLight);
	m_CameraSpeed = 5.0f;
	setCamera(std::make_shared<Camera>(glm::vec3(-10.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f, m_CameraSpeed, 0.1f, 60.0f, 0.1f, 100.0f, CAMERA_TYPE_PERSPECTIVE));
	setBackgroundColor(glm::vec3(0.0f, 1.0f, 0.0f));
	initializeSkybox();

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

	std::shared_ptr<ModelRenderData> ironmanRenderData = std::make_shared<ModelRenderData>(ironmanModelData, nullptr, shinyMaterial, rendererShader);
	std::shared_ptr<ModelRenderData> helicopterRenderData = std::make_shared<ModelRenderData>(helicopterModelDataNew, nullptr, shinyMaterial, rendererShader);

	std::shared_ptr<MeshRenderData> meshRenderData = std::make_shared<MeshRenderData>(createCubeMeshData(), spidermanTexture, shinyMaterial, rendererShader);
	std::shared_ptr<MeshRenderData> plainRenderData = std::make_shared<MeshRenderData>(createPlainMeshData(), spidermanTexture, roughMaterial, rendererShader);

	m_HelicopterBig = std::make_shared<ModelEntity>(helicopterRenderData);
	m_HelicopterBig->GetComponent<Transform>()->Translate(glm::vec3(0.0f, -7.0f, -10.0f));
	m_HelicopterBig->transform->Scale(glm::vec3(2.0f, 2.0f, 2.0f));
	m_HelicopterBig->transform->Rotate(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	m_HelicopterBig->transform->Rotate(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	m_HelicopterBig->setName("helicopterBig");
	instantiateGameEntity(m_HelicopterBig);

	m_HelicopterSmall = std::make_shared<ModelEntity>(helicopterRenderData);
	m_HelicopterSmall->setName("helicopterSmall");
	instantiateGameEntity(m_HelicopterSmall);

	ironman = std::make_shared<ModelEntity>(ironmanRenderData);
	ironman->setName("ironMAn");
	instantiateGameEntity(ironman);

	std::shared_ptr<MeshEntity> cubeMeshEntity = std::make_shared<MeshEntity>(meshRenderData);
	cubeMeshEntity->GetComponent<Transform>()->Translate(glm::vec3(36.0f, -7.0f, -12.0f));
	cubeMeshEntity->transform->Scale(glm::vec3(3.0f, 3.0f, 1.5f));
	cubeMeshEntity->setName("cubeMesh");
	instantiateGameEntity(cubeMeshEntity);

	std::shared_ptr<MeshEntity> spidermanPlainEntity = std::make_shared<MeshEntity>(plainRenderData);
	spidermanPlainEntity->GetComponent<Transform>()->Translate(glm::vec3(0.0f, -10.0f, 0.0f));
	spidermanPlainEntity->transform->Scale(glm::vec3(1.0f, 1.0f, 1.0f));
	spidermanPlainEntity->setName("spidermanPlain");
	instantiateGameEntity(spidermanPlainEntity);

	std::shared_ptr<MeshEntity> spidermanCubeEntity = std::make_shared<MeshEntity>(meshRenderData);
	spidermanCubeEntity->transform->Translate(glm::vec3(15.0f, 10.0f, 15.0f));
	spidermanCubeEntity->transform->Scale(glm::vec3(3.0f, 3.0f, 3.0f));
	spidermanCubeEntity->setName("spidermanCube");
	instantiateGameEntity(spidermanCubeEntity);
	

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
	//addSpotLight(new SpotLight(0.0f, 155.0f,
	//	0.0f, 0.5f, 1.0f,
	//	0.0f, -10.0f, 0.0f,
	//	0.0f, 0.5f, 0.0f,
	//	0.1f, 0.1f, 0.1f,
	//	100.0f,
	//	0.01f, 200.0f));
	addSpotLight(new SpotLight(0.0f, 100.0f,
		0.0f, 1.0f, 1.0f,
		-7.0f, 12.0f, 8.0f,
		0.7f, -0.6f, 0.3f,
		0.8f, 0.01f, 0.8f,
		100.0f,
		1024, 1024,
		0.01f, 200.0f));
}

void DemoScene3D::Start()
{
	ironman->transform->Translate(glm::vec3(20.0f, 10.0f, -10.0f));
	ironman->transform->Scale(glm::vec3(0.2f, 0.2f, 0.2f));
	ironman->transform->Rotate(-60.0f, glm::vec3(0.0f, 1.0f, 0.0f));

	m_HelicopterSmall->transform->Rotate(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	m_HelicopterSmall->transform->Rotate(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}

float ironmanTimeCounter = 0.0f;
float rotate = 0.0f;
float positionY = 0.0f;
float increaseValue = 1.5f;
void DemoScene3D::Update(GLfloat deltaTime)
{
	ironmanTimeCounter += deltaTime;
	m_DeltaTime = deltaTime;
	rotate = deltaTime * 12.5f;
	positionY += deltaTime * increaseValue;
	if (positionY > 4)
	{
		increaseValue = -1.5f;
	}
	if (positionY < 1)
	{
		increaseValue = 1.5f;
	}

	m_HelicopterBig->transform->Rotate(rotate, glm::vec3(0.0f, 0.0, 1.0f));
	m_HelicopterBig->transform->Translate(glm::vec3(0.0f, increaseValue * deltaTime, 0.0f));
	m_HelicopterSmall->transform->Rotate(rotate, glm::vec3(0.0f, 0.0, 1.0f));
	ironman->transform->Translate(glm::vec3(0.0f, increaseValue, 0.0f));

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
void DemoScene3D::handleOnRightKey()
{
	m_MainCamera->MoveRight(m_CameraSpeed * m_DeltaTime);
}

void DemoScene3D::handleOnLeftKey()
{
	m_MainCamera->MoveLeft(m_CameraSpeed * m_DeltaTime);
}

void DemoScene3D::handleOnUpKey()
{
	m_MainCamera->MoveForward(m_CameraSpeed * m_DeltaTime);
}

void DemoScene3D::handleOnDownKey()
{
	m_MainCamera->MoveBack(m_CameraSpeed * m_DeltaTime);
}

void DemoScene3D::handleOnShiftKey()
{
	m_CameraSpeed = 15.0f;
}

void DemoScene3D::handleOnShiftReleasedKey()
{
	m_CameraSpeed = 5.0f;
}


void DemoScene3D::handleOnSpaceKey()
{
	if (ironmanTimeCounter > 2.0f)
	{
		//ironman->setActive(!ironman->getActive());
		destroyGameEntity(ironman, false);
		ironmanTimeCounter = 0.0f;
	}
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
	LOG_INFO("Demo scene initialized3!");
}


