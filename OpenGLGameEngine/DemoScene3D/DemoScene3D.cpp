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
	shader = Shader();
	shader.CreateFromFiles(vShaderLocation, fShaderLocation);

	//setDirectionalLight(new DirectionalLight(0.1f, 0.1f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 2048, 2048));

	setCamera(new Camera(glm::vec3(-10.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f, 5.0f, 0.1f));
	setBackgroundColor(glm::vec3(0.0f, 1.0f, 0.0f));

	initializeSkybox();

	shinyMaterial = Material(5.0f, 45.5f);
	roughMaterial = Material(0.5f, 4.0f);
	shinyRenderer = Renderer(&shinyMaterial, &shader);

	ironmanModel = Model();
	ironmanModel.LoadModel("Models/IronMan.obj");
	spidermanTexture = Texture("Textures/spiderman.png");
	spidermanTexture.LoadTextureWithAlpha();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureWithAlpha();

	Model* helicopterModelData = new Model();
	helicopterModelData->LoadModel("Models/uh60.obj");
	helicopterRenderableData = RenderableData(helicopterModelData);
	helicopter = new RenderableObject(&shinyRenderer, &helicopterRenderableData);

	RenderableData* spidermanCubeData = new RenderableData(createPlainMesh(), &spidermanTexture);
	spidermanCube = new RenderableObject(&shinyRenderer, spidermanCubeData);
}

void DemoScene3D::Start()
{

	helicopter->RotateTransform(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	helicopter->RotateTransform(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	helicopter->ScaleTransform(glm::vec3(1.0f, 1.0f, 1.0f));

	spidermanCube->TranslateTransform(glm::vec3(0.0f, -10.0f, 0.0f));
	spidermanCube->ScaleTransform(glm::vec3(1.0f, 1.0f, 1.0f));

	AddObject(helicopter);
	AddObject(spidermanCube);
}

void DemoScene3D::Update(GLfloat deltaTime)
{

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



