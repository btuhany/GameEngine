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

const float toRadians = 3.14159265f / 180.0f;

std::vector<Mesh*> meshList;
std::vector<Shader*> shaderList;

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
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] =
	{
		-1.0f, -1.0f, 0.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 12, 12);
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
	Window* mainWindow = new Window();
	mainWindow->Initialise();

	CreateObject();

	CreateShaders();


	GLuint uniformModel = 0;
	GLuint uniformProjection = 0;

	//unifrom value setted once
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow->getBufferWidth() / mainWindow->getBufferHeight(), 0.1f, 100.0f);

	
	//Loop until window closed
	while (!mainWindow->getShouldClose())
	{
		//Get and handle user inpu events
		glfwPollEvents();

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

		shaderList[0]->UseShader();

		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, triOffset, -2.0f));
		model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.7f));

		//setting model matrix inside the shader
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//setting projection matrix 
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

		meshList[0]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(triOffset, 0.0f, -2.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.7f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();

		glUseProgram(0);

		mainWindow->swapBuffers();
	}

	printf("Window closed!");

	///* Clear */
	//glfwDestroyWindow(mainWindow);
	//glfwTerminate();

	return 0;
}
