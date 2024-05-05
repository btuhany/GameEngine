#include "DemoScene3D.h"

DemoScene3D::DemoScene3D()
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

	m_MainCamera = new Camera(glm::vec3(-10.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f, 5.0f, 0.1f);


	ironmanModel = Model();
	ironmanModel.LoadModel("Models/IronMan.obj");

	spidermanTexture = Texture("Textures/spiderman.png");
	spidermanTexture.LoadTextureWithAlpha();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureWithAlpha();

	Model* helicopterModelData = new Model();
	helicopterModelData->LoadModel("Models/uh60.obj");
	helicopterRenderableData = RenderableData(helicopterModelData, &spidermanTexture);


	shinyMaterial = Material(5.0f, 45.5f);
	roughMaterial = Material(0.5f, 4.0f);
	shinyRenderer = Renderer(&shinyMaterial, &shader);
}

void DemoScene3D::Start()
{
	RenderableObject* obj1 = new RenderableObject(&shinyRenderer, &helicopterRenderableData);
	obj1->RotateTransform(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	obj1->RotateTransform(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	obj1->ScaleTransform(glm::vec3(1.0f, 1.0f, 1.0f));

	RenderableData* renderableData2 = new RenderableData(createCubeMesh(), &spidermanTexture);
	RenderableObject* obj2 = new RenderableObject(&shinyRenderer, renderableData2);
	obj2->ScaleTransform(glm::vec3(10.0f, 10.0f, 10.0f));

	AddObject(obj1);
	AddObject(obj2);
}

void DemoScene3D::Update(glm::mat4 projection, GLfloat deltaTime)
{
	renderScene(projection);
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



