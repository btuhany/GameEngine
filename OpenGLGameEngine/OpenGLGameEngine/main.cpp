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

const float toRadians = 3.14159265f / 180.0f;

std::vector<Mesh*> meshList;
std::vector<Shader*> shaderList;
Camera mainCamera;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

bool direction = true;
float triOffset = 0.0f;
float triMaxoffset = 1.0f;
float triIncrement = 0.005f;
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
		0, 1, 9,
		0, 10, 9,
		2, 3, 4,
		2, 5, 4,
		6, 7, 8,
		6, 9, 8,
		11, 12, 20,
		11, 21, 20,
		13, 14, 15,
		13, 16, 15,
		17, 18, 19,
		17, 20, 19,
		0, 10, 11,
		11, 21, 10,
		0, 1, 12,
		0, 11, 12,
		//1, 12, 13,
		//1, 2, 13,
		2, 3, 14,
		2, 13, 14,
		3, 4, 15,
		14, 3, 15,
		4, 15, 5,
		5, 16, 15,
		1, 6, 17, 
		12, 1, 17,
		6, 17, 18,
		18, 7 , 6,
		7, 8, 19,
		19, 18, 7,
		8, 19, 21,
		21, 10, 8
	};

	

	GLfloat vertices[] =
	{
		0.0f, 0.0f, 2.0f,
		1.0f, 0.0f, 2.0f,
		1.0f, 3.0f, 2.0f,
		2.0f, 3.0f, 2.0f,
		2.0f, 4.0f, 2.0f,
		1.0f, 4.0f, 2.0f,
		1.0f, 5.0f, 2.0f,
		4.0f, 5.0f, 2.0f,
		4.0f, 6.0f, 2.0f,
		1.0f, 6.0f, 2.0f,
		0.0f, 6.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 3.0f, 0.0f,
		2.0f, 3.0f, 0.0f,
		2.0f, 4.0f, 0.0f,
		1.0f, 4.0f, 0.0f,
		1.0f, 5.0f, 0.0f,
		4.0f, 5.0f, 0.0f,
		4.0f, 6.0f, 0.0f,
		1.0f, 6.0f, 0.0f,
		0.0f, 6.0f, 0.0f
	};



	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 66, 90);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 66, 90);
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
	Window mainWindow = Window(1920, 1080);
	mainWindow.Initialize();

	CreateObject();
	CreateShaders();
	mainCamera = Camera(glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f, 0.0f, 5.0f, 0.1f);

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
			triOffset += triIncrement;
		}
		else
		{
			triOffset -= triIncrement;
		}

		if (abs(triOffset) >= triMaxoffset)
		{
			direction = !direction;
		}

		curAngle += 0.3f;
		//if (curAngle > 360)
		{
			//curAngle = 0.0f;
		}

		if (direction)
		{
			curSize += 0.001f;
		}
		else
		{
			curSize -= 0.001f;
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
		model = glm::translate(model, glm::vec3(0.0f, triOffset, -2.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		model = glm::rotate(model, 2 * curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));

		//setting model matrix inside the shader
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//setting projection matrix 
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(mainCamera.CalculateViewMatrix()));

		meshList[0]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-triOffset, 0.0f, -4.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
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
