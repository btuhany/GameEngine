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
	LOG_INFO("Demo scene initialized!");
	m_InputReader->OnPresssedRightEvent.AddHandler([this]() {handleOnRightKey();});
	m_InputReader->OnPresssedDownEvent.AddHandler([this]() {handleOnDownKey();});
	m_InputReader->OnPresssedLeftEvent.AddHandler([this]() {handleOnLeftKey();});
	m_InputReader->OnPresssedUpEvent.AddHandler([this]() {handleOnUpKey();});
	m_InputReader->OnPressedShiftEvent.AddHandler([this]() {handleOnShiftKey();});
	m_InputReader->OnReleasedShiftEvent.AddHandler([this]() {handleOnShiftReleasedKey();});
	static const char* vShaderLocation = "src/DemoScene3D/Shaders/shader.vert";
	static const char* fShaderLocation = "src/DemoScene3D/Shaders/shader.frag";
	Shader* rendererShader = new Shader();
	rendererShader->CreateFromFiles(vShaderLocation, fShaderLocation);

	Shader* rendererShader2 = new Shader();
	rendererShader2->CreateFromFiles(vShaderLocation, fShaderLocation);

	Shader* directionalShadowShader = new Shader();
	directionalShadowShader->CreateFromFiles("src/DemoScene3D/Shaders/directional_shadow_map.vert", "src/DemoScene3D/Shaders/directional_shadow_map.frag");

	Shader* omniShadowShader = new Shader();
	omniShadowShader->CreateFromFiles("src/DemoScene3D/Shaders/omni_shadow_map.vert", "src/DemoScene3D/Shaders/omni_shadow_map.geom", "src/DemoScene3D/Shaders/omni_shadow_map.frag");
	setOmniShadowShader(omniShadowShader);
	LOG_INFO("Demo scene initialized2!");
	DirectionalLight* dirLight = new DirectionalLight(0.0f, 0.05f,
		0.2f, 0.5f, 1.0f,
		0.4f, -0.8f, 0.01f, 1024, 1024);
	SetDirectionalLight(dirLight);
	m_CameraSpeed = 5.0f;
	setCamera(new Camera(glm::vec3(-10.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f, m_CameraSpeed, 0.1f, 60.0f, 0.1f, 100.0f, CAMERA_TYPE_PERSPECTIVE));
	setBackgroundColor(glm::vec3(0.0f, 1.0f, 0.0f));
	initializeSkybox();

	Material* shinyMaterial = new Material(590.0f, 475.5f);
	Material* roughMaterial = new Material(0.1f, 3.0f);

	Texture* spidermanTexture = new Texture("src/DemoScene3D/Textures/spiderman.png");
	spidermanTexture->LoadTextureWithAlpha();
	Texture* plainTexture = new Texture("src/DemoScene3D/Textures/plain.png");
	plainTexture->LoadTextureWithAlpha();

	ModelData* helicopterModelDataNew = new ModelData();
	helicopterModelDataNew->LoadModel("src/DemoScene3D/Models/uh60.obj");
	m_HelicopterBig = std::make_shared<ModelEntity>();
	std::shared_ptr<ModelRenderData> helicopterRenderData = std::make_shared<ModelRenderData>();
	helicopterRenderData->modelData = helicopterModelDataNew;
	//helicopterRenderData->textureData = spidermanTexture;
	helicopterRenderData->materialData = shinyMaterial;
	helicopterRenderData->shader = rendererShader;
	m_HelicopterBig->renderer->camera = m_MainCamera;
	m_HelicopterBig->renderer->directionalLight = dirLight;
	m_HelicopterBig->renderer->omniShadowShader = omniShadowShader;
	m_HelicopterBig->renderer->modelRenderData = helicopterRenderData;
	m_HelicopterBig->renderer->dirShadowShader = directionalShadowShader;
	RenderableEntitiesPublic.push_back(m_HelicopterBig);
	m_HelicopterBig->GetComponent<Transform>()->Translate(glm::vec3(0.0f, -7.0f, -10.0f));
	m_HelicopterBig->transform->Scale(glm::vec3(2.0f, 2.0f, 2.0f));
	m_HelicopterBig->transform->Rotate(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	m_HelicopterBig->transform->Rotate(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	RenderableModelEntitiesPublic.push_back(m_HelicopterBig);

	m_HelicopterSmall = std::make_shared<ModelEntity>();
	m_HelicopterSmall->renderer->camera = m_MainCamera;
	m_HelicopterSmall->renderer->directionalLight = dirLight;
	m_HelicopterSmall->renderer->omniShadowShader = omniShadowShader;
	m_HelicopterSmall->renderer->modelRenderData = helicopterRenderData;
	m_HelicopterSmall->renderer->dirShadowShader = directionalShadowShader;
	RenderableEntitiesPublic.push_back(m_HelicopterSmall);
	RenderableModelEntitiesPublic.push_back(m_HelicopterSmall);

	std::shared_ptr<MeshEntity> cubeMeshEntity = std::make_shared<MeshEntity>();
	std::shared_ptr<MeshRenderData> meshRenderData = std::make_shared<MeshRenderData>();
	meshRenderData->meshData = createCubeMeshData();
	meshRenderData->textureData = spidermanTexture;
	meshRenderData->materialData = shinyMaterial;
	meshRenderData->shader = rendererShader;
	cubeMeshEntity->renderer->camera = m_MainCamera;
	cubeMeshEntity->renderer->directionalLight = dirLight;
	cubeMeshEntity->renderer->omniShadowShader = omniShadowShader;
	cubeMeshEntity->renderer->meshRenderData = meshRenderData;
	cubeMeshEntity->renderer->dirShadowShader = directionalShadowShader;
	RenderableEntitiesPublic.push_back(cubeMeshEntity);
	RenderableMeshEntitiesPublic.push_back(cubeMeshEntity);
	cubeMeshEntity->GetComponent<Transform>()->Translate(glm::vec3(36.0f, -7.0f, -12.0f));
	cubeMeshEntity->transform->Scale(glm::vec3(3.0f, 3.0f, 1.5f));

	ModelData* ironmanModelData = new ModelData();
	ironmanModelData->LoadModel("src/DemoScene3D/Models/IronMan.obj");
	ironman = std::make_shared<ModelEntity>();
	std::shared_ptr<ModelRenderData> ironmanRenderData = std::make_shared<ModelRenderData>();
	ironmanRenderData->modelData = ironmanModelData;
	//modelRenderData->textureData = spidermanTexture;
	ironmanRenderData->materialData = shinyMaterial;
	ironmanRenderData->shader = rendererShader;
	ironman->renderer->camera = m_MainCamera;
	ironman->renderer->directionalLight = dirLight;
	ironman->renderer->omniShadowShader = omniShadowShader;
	ironman->renderer->modelRenderData = ironmanRenderData;
	ironman->renderer->dirShadowShader = directionalShadowShader;
	RenderableEntitiesPublic.push_back(ironman);
	RenderableModelEntitiesPublic.push_back(ironman);

	std::shared_ptr<MeshEntity> spidermanPlainEntity = std::make_shared<MeshEntity>();
	std::shared_ptr<MeshRenderData> plainRenderData = std::make_shared<MeshRenderData>();
	plainRenderData->meshData = createPlainMeshData();
	plainRenderData->textureData = spidermanTexture;
	plainRenderData->materialData = roughMaterial;
	plainRenderData->shader = rendererShader;
	spidermanPlainEntity->renderer->camera = m_MainCamera;
	spidermanPlainEntity->renderer->directionalLight = dirLight;
	spidermanPlainEntity->renderer->meshRenderData = plainRenderData;
	spidermanPlainEntity->renderer->dirShadowShader = directionalShadowShader;
	spidermanPlainEntity->renderer->omniShadowShader = omniShadowShader;
	RenderableEntitiesPublic.push_back(spidermanPlainEntity);
	RenderableMeshEntitiesPublic.push_back(spidermanPlainEntity);
	spidermanPlainEntity->GetComponent<Transform>()->Translate(glm::vec3(0.0f, -10.0f, 0.0f));
	spidermanPlainEntity->transform->Scale(glm::vec3(1.0f, 1.0f, 1.0f));


	std::shared_ptr<MeshEntity> spidermanCubeEntity = std::make_shared<MeshEntity>();
	spidermanCubeEntity->renderer->camera = m_MainCamera;
	spidermanCubeEntity->renderer->directionalLight = dirLight;
	spidermanCubeEntity->renderer->meshRenderData = meshRenderData;
	spidermanCubeEntity->renderer->dirShadowShader = directionalShadowShader;
	spidermanCubeEntity->renderer->omniShadowShader = omniShadowShader;
	RenderableEntitiesPublic.push_back(spidermanCubeEntity);
	RenderableMeshEntitiesPublic.push_back(spidermanCubeEntity);
	spidermanCubeEntity->transform->Translate(glm::vec3(15.0f, 10.0f, 15.0f));
	spidermanCubeEntity->transform->Scale(glm::vec3(3.0f, 3.0f, 3.0f));

	

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
		1024,1024,
		0.01f, 300.0f));
	addSpotLight(new SpotLight(0.0f, 80.5f,
		 1.0f, 0.0f, 0.0f,
		0.0f, 20.0f, 0.0f,
		0.0f, -1.0f, 0.6f,
		1.1f, 1.0f, 0.01f,
		60.0f,
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

void DemoScene3D::Start()
{
	ironman->transform->Translate(glm::vec3(20.0f, 10.0f, -10.0f));
	ironman->transform->Scale(glm::vec3(0.2f, 0.2f, 0.2f));
	ironman->transform->Rotate(-60.0f, glm::vec3(0.0f, 1.0f, 0.0f));

	m_HelicopterSmall->transform->Rotate(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	m_HelicopterSmall->transform->Rotate(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}

float rotate = 0.0f;
float positionY = 0.0f;
float increaseValue = 1.5f;
void DemoScene3D::Update(GLfloat deltaTime)
{
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

MeshData* DemoScene3D::createCubeMeshData()
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

	MeshData* cubeMesh = new MeshData();
	cubeMesh->CreateMesh(vertices, indices, 64, 36);
	return cubeMesh;
}

MeshData* DemoScene3D::createPlainMeshData()
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

	MeshData* plainMesh = new MeshData();
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
	useSkybox(true);
	LOG_INFO("Demo scene initialized3!");
}


