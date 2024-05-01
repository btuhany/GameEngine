#pragma once
#include "Core/Engine.h"
#include "Core/Camera.h"
#include "Core/Object.h"
#include "DemoScene3D.h"

// Vertex shader
static const char* vShaderLocation = "Shaders/shader.vert";

// Fragment shader
static const char* fShaderLocation = "Shaders/shader.frag";


int main()
{
	DemoScene3D scene;

	Engine engine = Engine(new Window(1366, 768));
	engine.Initialize(&scene);

	engine.Start();


	Shader* shader = new Shader();
	shader->CreateFromFiles(vShaderLocation, fShaderLocation);
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






	Texture spidermanTexture = Texture("Textures/spiderman.png");
	spidermanTexture.LoadTextureWithAlpha();
	Material shinyMaterial = Material(5.0f, 45.5f);
	Mesh* mesh1 = new Mesh();
	mesh1->CreateMesh(vertices, indices, 64, 36);

	Renderer renderer = Renderer(mesh1 , &spidermanTexture, &shinyMaterial, shader);
	Object obj1 = Object(&renderer);
	obj1.ScaleTransform(glm::vec3(10.0f, 10.0f, 10.0f));
	scene.AddObject(&obj1);
		
	engine.Run();

	return 0;

}