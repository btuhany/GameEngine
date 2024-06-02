#include "DemoScene3D.h"

DemoScene3D::DemoScene3D() : Scene()
{
}

DemoScene3D::~DemoScene3D()
{
}

void DemoScene3D::Initialize()
{
	static const char* vShaderLocation = "Shaders/shader.vert";
	static const char* fShaderLocation = "Shaders/shader.frag";
	m_Shader = new Shader();
	m_Shader->CreateFromFiles(vShaderLocation, fShaderLocation);

	registerRenderShader(m_Shader);

	m_DirectionalShadowShader = new Shader();
	m_DirectionalShadowShader->CreateFromFiles("Shaders/directional_shadow_map.vert", "Shaders/directional_shadow_map.frag");

	m_OmniShadowShader = new Shader();
	m_OmniShadowShader->CreateFromFiles("Shaders/omni_shadow_map.vert", "Shaders/omni_shadow_map.geom", "Shaders/omni_shadow_map.frag");

	setDirectionalLight(new DirectionalLight(0.1f, 0.1f, 
		0.0f, 0.0f, 0.0f, 
		0.3f, -1.0f, 0.01f,
		2048, 2048));
	setCamera(new Camera(glm::vec3(-10.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f, 5.0f, 0.1f));
	setBackgroundColor(glm::vec3(0.0f, 1.0f, 0.0f));

	initializeSkybox();

	shinyMaterial = Material(0.5f, 10.5f);
	roughMaterial = Material(0.5f, 4.0f);

	shinyRenderer = Renderer(&shinyMaterial, m_Shader, m_DirectionalShadowShader, m_OmniShadowShader);
	roughRenderer = Renderer(&roughMaterial, m_Shader, m_DirectionalShadowShader, m_OmniShadowShader);

	spidermanTexture = new Texture("Textures/spiderman.png");
	spidermanTexture->LoadTextureWithAlpha();
	plainTexture = new Texture("Textures/plain.png");
	plainTexture->LoadTextureWithAlpha();

	helicopterModelData = new Model();
	helicopterModelData->LoadModel("Models/uh60.obj");
	helicopterRenderableData = new RenderableData(helicopterModelData);
	helicopter = new RenderableObject(&shinyRenderer, helicopterRenderableData);

	ironmanModelData = new Model();
	ironmanModelData->LoadModel("Models/IronMan.obj");
	ironmanRenderableData = new RenderableData(ironmanModelData);
	ironman = new RenderableObject(&shinyRenderer, ironmanRenderableData);

	RenderableData* spidermanCubeData = new RenderableData(createPlainMesh(), spidermanTexture);
	spidermanCube = new RenderableObject(&shinyRenderer, spidermanCubeData);

	AddPointLight(new PointLight(0.0f, 155.5f,
		0.0f, 1.0f, 0.0f,
		7.0f, 15.0f, 5.0f,
		1.0f, 1.0f, 0.5f,
		2048, 2048,
		0.01f, 100.0f));
	AddSpotLight(new SpotLight(0.0f, 700.5f,
		 1.0f, 0.0f, 0.0f,
		-30.0f, 0.0f, 15.0f,
		0.0f, -1.0f, 0.6f,
		5.0f, 1.0f, 1.0f,
		60.0f,
		2048, 2048,
		0.01f, 100.0f));
	AddPointLight(new PointLight(0.0f, 255.5f,
		1.0f, 0.7f, 0.7f,
		0.0f, 30.0f, -20.0f,
		0.5f, 0.5f, 0.1f,
		4096, 4096,
		0.01f, 300.0f));
	AddSpotLight(new SpotLight(0.0f, 255.0f,
		0.0f, 0.5f, 1.0f,
		-5.0, 20.0f, -20.0f,
		0.0f, -0.2f, 1.0f,
		0.5f, 0.5f, 0.1f, 
		70.0f,
		2048, 2048,
		0.01f, 200.0f));
}

void DemoScene3D::Start()
{
	ironman->TranslateTransform(glm::vec3(20.0f, 10.0f, -10.0f));
	ironman->ScaleTransform(glm::vec3(0.2f, 0.2f, 0.2f));
	ironman->RotateTransform(-60.0f, glm::vec3(0.0f, 1.0f, 0.0f));

	helicopter->RotateTransform(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	helicopter->RotateTransform(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	helicopter->ScaleTransform(glm::vec3(1.0f, 1.0f, 1.0f));

	spidermanCube->TranslateTransform(glm::vec3(0.0f, -10.0f, 0.0f));
	spidermanCube->ScaleTransform(glm::vec3(1.0f, 1.0f, 1.0f));

	AddObject(ironman);
	AddObject(helicopter);
	AddObject(spidermanCube);
}

float rotate = 0.0f;
float positionY = 0.0f;
float increaseValue = 1.5f;
void DemoScene3D::Update(GLfloat deltaTime)
{
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

	helicopter->RotateTransform(rotate, glm::vec3(0.0f, 0.0, 1.0f));
	ironman->TranslateTransform(glm::vec3(0.0f, increaseValue, 0.0f));

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

void DemoScene3D::initializeSkybox()
{
	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/skybox/cupertin-lake_ft.tga");
	Skybox* skybox = new Skybox(skyboxFaces);
	setSkybox(skybox);
	useSkybox(true);
}



