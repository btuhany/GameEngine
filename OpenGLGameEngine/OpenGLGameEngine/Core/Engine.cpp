#include "Engine.h"


Engine::Engine(Window* window)
{
	m_MainWindow = window;
	m_IsInitialized = false;
}

Engine::~Engine()
{
	m_Scene = nullptr;
}

void Engine::Initialize(Scene* scene)
{
	m_MainWindow->Initialize();
	m_Scene = scene;
	m_Scene->Initialize();
	m_IsInitialized = true;
}

void Engine::Start()
{
	if (!m_IsInitialized)
	{
		std::cout << "Engine is not initialized! Failed to start." << std::endl;
		return;
	}
	m_Scene->Start();
}

void Engine::Run()
{
	GLfloat deltaTime = 0.0f;
	GLfloat lastTime = 0.0f;

	while (!m_MainWindow->GetShouldClose())
	{
		GLfloat timeNow = glfwGetTime(); //SDL_GetPerformanceCounter();
		deltaTime = timeNow - lastTime; // (timeNow - lastTime)*1000 / SDL_GetPerformanceFrequency();
		lastTime = timeNow;

		glfwPollEvents();



		glViewport(0, 0, 1366, 768);
		//Clear window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_Scene->GetCamera()->HandleKeys(m_MainWindow->GetKeys(), deltaTime);
		m_Scene->GetCamera()->HandleMouse(m_MainWindow->GetMouseDeltaX(), m_MainWindow->GetMouseDeltaY());

		glm::mat4 projection = glm::perspective(glm::radians(60.0f), (GLfloat)m_MainWindow->GetBufferWidth() / m_MainWindow->GetBufferHeight(), 0.1f, 100.0f);

		m_Scene->Update(projection, deltaTime);

		m_MainWindow->SwapBuffers();
	}
}

void Engine::Stop()
{
}
