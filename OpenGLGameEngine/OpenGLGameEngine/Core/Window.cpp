#include "Window.h"

Window::Window()
{
	m_Width = 800;
	m_Height = 600;

	m_MouseLastXPosition = 0;
	m_MouseLastYPosition = 0;
	m_MouseDeltaX = 0;
	m_MouseDeltaY = 0;

	for (size_t i = 0; i < 1024; i++)
	{
		m_Keys[i] = 0;
	}
}

Window::Window(GLint windowWidth, GLint windowHeight)
{
	m_Width = windowWidth;
	m_Height = windowHeight;

	m_MouseLastXPosition = 0;
	m_MouseLastYPosition = 0;
	m_MouseDeltaX = 0;
	m_MouseDeltaY = 0;

	for (size_t i = 0; i < 1024; i++)
	{
		m_Keys[i] = 0;
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

	m_MainWindow = glfwCreateWindow(m_Width, m_Height, "Test Window", NULL, NULL);
	if (!m_MainWindow)
	{
		printf("GLFW window creation failed!");
		glfwTerminate();
		return 1;
	}

	//Get buffer size information (Actual viewport)
	glfwGetFramebufferSize(m_MainWindow, &m_BufferWidth, &m_BufferHeight);

	//Set context for GLEW to use (if you need multiple windows you can switch)
	//Important!
	glfwMakeContextCurrent(m_MainWindow);

	//Handle Key + Mouse Input
	createCallbacks();
	glfwSetInputMode(m_MainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//Allow modern extension features
	glewExperimental = GL_TRUE;

	// Check Glew
	if (glewInit() != GLEW_OK)
	{
		printf("GLEW initialization failed!");
		glfwDestroyWindow(m_MainWindow);  //window created by glew
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST);

	//Setup viewport size
	glViewport(0, 0, m_BufferWidth, m_BufferHeight);

	//For reading input
	glfwSetWindowUserPointer(m_MainWindow, this);
	
	return 0;
}

GLfloat Window::GetMouseDeltaX()
{
	GLfloat deltaX = m_MouseDeltaX;
	m_MouseDeltaX = 0.0f;
	return deltaX;
}

GLfloat Window::GetMouseDeltaY()
{
	GLfloat deltaY = m_MouseDeltaY;
	m_MouseDeltaY = 0.0f;
	return deltaY;
}

Window::~Window()
{
	glfwDestroyWindow(m_MainWindow);  //window created by glew
	glfwTerminate();
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(m_MainWindow, handleKeys);
	glfwSetCursorPosCallback(m_MainWindow, handleMouse);
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
			theWindow->m_Keys[key] = true;
			printf("Pressed: %d\n", key);
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->m_Keys[key] = false;
			printf("Released: %d\n", key);
		}
	}
}

void Window::handleMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->m_MouseFirstMoved)
	{
		theWindow->m_MouseLastXPosition = xPos;
		theWindow->m_MouseLastYPosition = yPos;
		theWindow->m_MouseFirstMoved = false;
	}
	theWindow->m_MouseDeltaX = xPos - theWindow->m_MouseLastXPosition;
	theWindow->m_MouseDeltaY = theWindow->m_MouseLastYPosition - yPos;

	theWindow->m_MouseLastXPosition = xPos;
	theWindow->m_MouseLastYPosition = yPos;

	//printf("Mouse Pos X: %.6f\n", theWindow->mouseDeltaX);
	//printf("Mouse Pos Y: %.6f\n", yPos);
}
