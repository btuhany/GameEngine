#include "Window.h"

Window::Window()
{
	width = 800;
	height = 600;

	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}

Window::Window(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;

	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}

int Window::Initialize()
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

	//Handle Key + Mouse Input
	createCallbacks();
	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

	//For reading input
	glfwSetWindowUserPointer(mainWindow, this);
	
	return 0;
}

GLfloat Window::GetMouseDeltaX()
{
	return GLfloat();
}

GLfloat Window::GetMouseDeltaY()
{
	return GLfloat();
}

Window::~Window()
{
	glfwDestroyWindow(mainWindow);  //window created by glew
	glfwTerminate();
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(mainWindow, handleKeys);
	glfwSetCursorPosCallback(mainWindow, handleMouse);
}

void Window::handleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
			printf("Pressed: %d\n", key);
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
			printf("Released: %d\n", key);
		}
	}
}

void Window::handleMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->mouseFirstMoved)
	{
		theWindow->mouseLastXPosition = xPos;
		theWindow->mouseLastYPosition = yPos;
		theWindow->mouseFirstMoved = false;
	}
	theWindow->mouseDeltaX = xPos - theWindow->mouseLastXPosition;
	theWindow->mouseDeltaY = theWindow->mouseLastYPosition - yPos;

	theWindow->mouseLastXPosition = xPos;
	theWindow->mouseLastYPosition = yPos;

	printf("Mouse Pos X: %.6f\n", theWindow->mouseDeltaX);
	//printf("Mouse Pos Y: %.6f\n", yPos);
}
