#include <stdio.h>
#include <string.h>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm\glm.hpp>
#include <glm/gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

//Window dimensions
const GLint WIDTH = 800, HEIGHT = 600;
const float toRadians = 3.14159265f / 180.0f;

GLuint VAO, VBO, shader, uniformModel;

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
static const char* vShader = "										\n\
#version 330														\n\
																	\n\
layout (location = 0) in vec3 pos;									\n\
																	\n\
uniform mat4 model;													\n\
																	\n\
																	\n\
out vec4 vCol;														\n\
void main()															\n\
{																	\n\
	gl_Position = model * vec4( pos.x, pos.y, pos.z, 1.0);			\n\
	vCol = vec4(clamp(pos, 0.0, 1.0), 1.0f);						\n\
}																	\n\
";

// Fragment shader
static const char* fShader = "				\n\
#version 330								\n\
											\n\
out vec4 colour;							\n\
											\n\
in vec4 vCol;								\n\
void main()									\n\
{											\n\
	colour = vCol;      \n\
}											\n\
";
void CreateTriangle()
{
	GLfloat vertices[] =
	{
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	//Creating the VAO, one array, where to store the id. 
	//Graphics card memory one vertex array and id
	glGenVertexArrays(1, &VAO);
	//Bind the VAO and Any opengl functions there will be taking place in this vao
	glBindVertexArray(VAO);
	 
		//Inside the VAO, we are creating the VBO and it gives the id and we take it with the VBO
		glGenBuffers(1, &VBO);
		//We want to bind the id of the vbo
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

			//Buffering the data
			//vertices to buffer data, pick the actual target to bind, 
			//in this case you can use the sizeof, 
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			//location (layout = 0 in shader), size of each value going to past in (in vertices)
			//each vertex position has three float value, so the size is 3. type is float.
			//we could use "3*sizeof(float)" instead of 0 stride value and "(void*)0" instead of void pointer idk why.
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			//enable location
			glEnableVertexAttribArray(0);

		//unbinding
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		printf("Error compiling the %d shader: '%s'\n", shaderType, eLog);
		return;
	}

	glAttachShader(theProgram, theShader);
}

void CompileShaders()
{
	shader = glCreateProgram();
	
	if (!shader)
	{
		printf("Error creating shader program!\n");
		return;
	}

	AddShader(shader, vShader, GL_VERTEX_SHADER);
	AddShader(shader, fShader, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shader);
	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("Error linking program: '%s'\n", eLog);
		return;
	}

	glValidateProgram(shader);
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("Error validating program: '%s'\n", eLog);
		return;
	}

	uniformModel = glGetUniformLocation(shader, "model");
}

int main()
{
	//Initialize GLFW
	if (!glfwInit())
	{
		printf("GLFW Initialization failed");
		glfwTerminate();
		return 1;
	}

	//Setup GLFW window properties
	//OpenGL version (3.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Core profile = NO backwards compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//Allow forward compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Test Window", NULL, NULL);
	if (!mainWindow)
	{
		printf("GLFW window creation failed!");
		glfwTerminate();
		return 1;
	}

	//Get buffer size information (Actual viewport)
	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight); 

	//Set context for GLEW to use (if you need multiple windows you can switch)
	//Important!
	glfwMakeContextCurrent(mainWindow);

	//Allow modern extension features
	glewExperimental = GL_TRUE;

	// Check Glew
	if (glewInit() != GLEW_OK)
	{
		printf("GLEW initialization failed!");
		glfwDestroyWindow(mainWindow);  //window created by glew
		glfwTerminate();
		return 1;
	}

	//Setup viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);

	CreateTriangle();
	CompileShaders();

	//Loop until window closed
	while (!glfwWindowShouldClose(mainWindow))
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

		curAngle += 1.0f;
		if (curAngle > 360)
		{
			curAngle = 0.0f;
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
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader);

		glm::mat4 model(1.0f);
		//model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::translate(model, glm::vec3(triOffset, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(curSize, 0.4f, 1.0f));

		//setting model matrix inside the shader
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

			glBindVertexArray(VAO);
				glDrawArrays(GL_TRIANGLES, 0, 3);
			glBindVertexArray(0);

		glUseProgram(0);

		glfwSwapBuffers(mainWindow);
	}

	printf("Window closed!");

	///* Clear */
	//glfwDestroyWindow(mainWindow);
	//glfwTerminate();

	return 0;
}
