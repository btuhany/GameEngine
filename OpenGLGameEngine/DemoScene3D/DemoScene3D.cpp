#include "DemoScene3D.h"

DemoScene3D::DemoScene3D()
{
}

DemoScene3D::~DemoScene3D()
{
}

void DemoScene3D::Initialize()
{
	Camera cam = Camera(glm::vec3(-10.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f, 5.0f, 0.1f);
	setCamera(cam);
}

void DemoScene3D::Start()
{
}

void DemoScene3D::Update(glm::mat4 projection, GLfloat deltaTime)
{
	renderScene(projection);
}

