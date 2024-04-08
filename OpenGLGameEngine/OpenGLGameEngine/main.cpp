#define STB_IMAGE_IMPLEMENTATION
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm\glm.hpp>
#include <glm/gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Mesh.h"
#include "Shader.h"
#include "Window.h"
#include "Camera.h"
#include "Texture.h"

const float toRadians = 3.14159265f / 180.0f;

std::vector<Mesh*> meshList;
std::vector<Shader*> shaderList;
Camera mainCamera;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

Texture spidermanTexture;
Texture learnopenglTexture;

bool direction = true;
float triOffset = 0.0f;
float triMaxoffset = 3.0f;
float triIncrement = 1.0f;
float curAngle = 0.0f;
float sizeDirection = true;
float curSize = 0.5f;
float maxSize = 1.0f;
float minSize = 0.1f;

// Vertex shader
static const char* vShaderLocation = "Shaders/shader.vert";

// Fragment shader
static const char* fShaderLocation = "Shaders/shader.frag";

void CreateObject()
{
	unsigned int indices[] = {
		0, 1, 2,
		0, 3, 2,
		2, 5, 4,
		2, 3, 4,
		3, 7, 4,
		3, 7, 0,
		0, 1, 6,
		0, 7, 6,
		6, 1, 2,
		6, 5, 2,
		5, 6, 4,
		6, 7, 4
	};

	

	GLfloat vertices[] =
	{
 		//x      y     z     u     y
		-1.0f, -1.0f, 1.0f, 1.0f, 0.0f,  //0
		1.0f, -1.0f, 1.0f,  0.0f, 0.0f,
		1.0f, -1.0f, -1.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f,   1.0f, 0.0f,
		-1.0f, 1.0f, 1.0f,  0.0f, 0.0f
	};



	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 40, 36);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 40, 36);
	meshList.push_back(obj2);
}
void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShaderLocation, fShaderLocation);
	shaderList.push_back(shader1);
}
int main()
{
	Window mainWindow = Window(720, 720);
	mainWindow.Initialize();

	CreateObject();
	CreateShaders();
	mainCamera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f, 5.0f, 0.1f);

	spidermanTexture = Texture("Textures/spiderman.png");
	spidermanTexture.LoadTexture();
	learnopenglTexture = Texture("Textures/learnopengl.png");
	learnopenglTexture.LoadTexture();

	GLuint uniformModel = 0;
	GLuint uniformProjection = 0;
	GLuint uniformView = 0;

	//unifrom value setted once
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.GetBufferWidth() / mainWindow.GetBufferHeight(), 0.1f, 100.0f);

	
	//Loop until window closed
	while (!mainWindow.GetShouldClose())
	{
		GLfloat timeNow = glfwGetTime(); //SDL_GetPerformanceCounter();
		deltaTime = timeNow - lastTime; // (timeNow - lastTime)*1000 / SDL_GetPerformanceFrequency();
		lastTime = timeNow;

		//Get and handle user inpu events
		glfwPollEvents();

		mainCamera.HandleKeys(mainWindow.GetKeys(), deltaTime);
		mainCamera.HandleMouse(mainWindow.GetMouseDeltaX(), mainWindow.GetMouseDeltaY());

		printf("Mouse Pos X: %.6f\n", mainWindow.GetMouseDeltaX());

		if (direction)
		{
			triOffset += triIncrement * deltaTime;
		}
		else
		{
			triOffset -= triIncrement * deltaTime;
		}

		if (abs(triOffset) >= triMaxoffset)
		{
			direction = !direction;
		}

		curAngle += 15.0f * deltaTime;;
		//if (curAngle > 360)
		{
			//curAngle = 0.0f;
		}

		if (direction)
		{
			curSize += 0.001f * deltaTime;;
		}
		else
		{
			curSize -= 0.001f * deltaTime;;
		}

		if (curSize > maxSize || curSize < minSize)
		{
			sizeDirection = !sizeDirection;
		}

		//Clear window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		uniformModel = shaderList[0]->GetModelLocation();
		uniformProjection = shaderList[0]->GetProjectionLocation();
		uniformView = shaderList[0]->GetViewLocation();

		shaderList[0]->UseShader();

		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, triOffset, -5.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.7f, 0.7f));
		model = glm::rotate(model, 2 * curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));

		//setting model matrix inside the shader
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//setting projection matrix 
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(mainCamera.CalculateViewMatrix()));
		learnopenglTexture.UseTexture();
		meshList[0]->RenderMesh();

		model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-triOffset, 0.0f, -10.0f));
		//model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		model = glm::rotate(model, 0.6f * curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		spidermanTexture.UseTexture();
		meshList[1]->RenderMesh();

		glUseProgram(0);

		mainWindow.SwapBuffers();
	}

	printf("Window closed!");

	///* Clear */
	//glfwDestroyWindow(mainWindow);
	//glfwTerminate();

	return 0;
}
