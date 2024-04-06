#include "Window.h"

Window::Window()
{
	width = 800;
	height = 600;
}

Window::Window(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
}

int Window::Initialise()
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

	mainWindow = glfwCreateWindow(width, height, "Test Window", NULL, NULL);
	if (!mainWindow)
	{
		printf("GLFW window creation failed!");
		glfwTerminate();
		return 1;
	}

	//Get buffer size information (Actual viewport)
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

	glEnable(GL_DEPTH_TEST);

	//Setup viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);
	return 0;
}

Window::~Window()
{
	glfwDestroyWindow(mainWindow);  //window created by glew
	glfwTerminate();
}
