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

	Shader* directionalShadowShader = new Shader();
	directionalShadowShader->CreateFromFiles("src/DemoScene3D/Shaders/directional_shadow_map.vert", "src/DemoScene3D/Shaders/directional_shadow_map.frag");

	Shader* omniShadowShader = new Shader();
	omniShadowShader->CreateFromFiles("src/DemoScene3D/Shaders/omni_shadow_map.vert", "src/DemoScene3D/Shaders/omni_shadow_map.geom", "src/DemoScene3D/Shaders/omni_shadow_map.frag");
	setOmniShadowShader(omniShadowShader);

	DirectionalLight* dirLight = new DirectionalLight(0.0f, 0.15f,
		0.0f, 0.5f, 1.0f,
		0.4f, -0.8f, 0.01f, 1024, 1024);
	SetDirectionalLight(dirLight);
	m_CameraSpeed = 5.0f;
	setCamera(new Camera(glm::vec3(-10.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f, m_CameraSpeed, 0.1f, 60.0f, 0.1f, 100.0f, CAMERA_TYPE_PERSPECTIVE));
	setBackgroundColor(glm::vec3(0.0f, 1.0f, 0.0f));

	initializeSkybox();

	Material* shinyMaterial = new Material(590.0f, 475.5f);
	Material* roughMaterial = new Material(0.1f, 3.0f);

	MeshRenderer* mainRenderer = new MeshRenderer(rendererShader, directionalShadowShader, omniShadowShader);
	mainRenderer->Initialize(m_MainCamera, dirLight);
	Texture* spidermanTexture = new Texture("src/DemoScene3D/Textures/spiderman.png");
	spidermanTexture->LoadTextureWithAlpha();
	Texture* plainTexture = new Texture("src/DemoScene3D/Textures/plain.png");
	plainTexture->LoadTextureWithAlpha();

	Model* helicopterModelData = new Model();
	helicopterModelData->LoadModel("src/DemoScene3D/Models/uh60.obj");
	RenderableData*  helicopterRenderableData = new RenderableData(helicopterModelData, shinyMaterial);
	helicopter = Renderable3DObject(mainRenderer, helicopterRenderableData);

	std::shared_ptr<MeshEntity> helicopterMeshEntity = std::make_shared<MeshEntity>();
	helicopterMeshEntity->m_RenderData = helicopterRenderableData;
	helicopterMeshEntity->m_Renderer = mainRenderer;
	RenderableEntitiesPublic.push_back(helicopterMeshEntity);

	Model* ironmanModelData = new Model();
	ironmanModelData->LoadModel("src/DemoScene3D/Models/IronMan.obj");
	RenderableData*  ironmanRenderableData = new RenderableData(ironmanModelData, shinyMaterial);
	ironman = Renderable3DObject(mainRenderer, ironmanRenderableData);

	RenderableData* spidermanPlainData = new RenderableData(createPlainMesh(), spidermanTexture, roughMaterial);
	spidermanPlain = Renderable3DObject(mainRenderer, spidermanPlainData);

	RenderableData* spidermanCubeData = new RenderableData(createCubeMesh(), spidermanTexture, shinyMaterial);
	spidermanCube = Renderable3DObject(mainRenderer, spidermanCubeData);
	

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
	addSpotLight(new SpotLight(0.0f, 500.0f,
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
	ironman.TranslateTransform(glm::vec3(20.0f, 10.0f, -10.0f));
	ironman.ScaleTransform(glm::vec3(0.2f, 0.2f, 0.2f));
	ironman.RotateTransform(-60.0f, glm::vec3(0.0f, 1.0f, 0.0f));

	helicopter.RotateTransform(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	helicopter.RotateTransform(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	helicopter.ScaleTransform(glm::vec3(1.0f, 1.0f, 1.0f));

	spidermanPlain.TranslateTransform(glm::vec3(0.0f, -10.0f, 0.0f));
	spidermanPlain.ScaleTransform(glm::vec3(1.0f, 1.0f, 1.0f));


	spidermanCube.TranslateTransform(glm::vec3(15.0f, 10.0f, 15.0f));
	spidermanCube.ScaleTransform(glm::vec3(3.0f, 3.0f, 3.0f));


	AddObject(&helicopter);
	AddObject(&spidermanPlain);
	AddObject(&spidermanCube);
	AddObject(&ironman);

	AddShadowMapRenderableObject(&helicopter);
	AddShadowMapRenderableObject(&spidermanPlain);
	AddShadowMapRenderableObject(&spidermanCube);
	AddShadowMapRenderableObject(&ironman);
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

	helicopter.RotateTransform(rotate, glm::vec3(0.0f, 0.0, 1.0f));
	ironman.TranslateTransform(glm::vec3(0.0f, increaseValue, 0.0f));

}

Mesh* DemoScene3D::createCubeMesh()
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

	Mesh* cubeMesh = new Mesh();
	cubeMesh->CreateMesh(vertices, indices, 64, 36);
	return cubeMesh;
}

Mesh* DemoScene3D::createPlainMesh()
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

	Mesh* plainMesh = new Mesh();
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
	Skybox* skybox = new Skybox(skyboxFaces, "src/DemoScene3D/Shaders/skybox.vert", "src/DemoScene3D/Shaders/skybox.frag");
	setSkybox(skybox);
	useSkybox(true);
}


