#define STB_IMAGE_IMPLEMENTATION
#include "Engine.h"

namespace GameEngine {
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
		glm::mat4 projection = glm::perspective(glm::radians(60.0f), (GLfloat)m_MainWindow->GetBufferWidth() / m_MainWindow->GetBufferHeight(), 0.1f, 100.0f);

		while (!m_MainWindow->GetShouldClose())
		{
			GLfloat timeNow = glfwGetTime(); //SDL_GetPerformanceCounter();
			deltaTime = timeNow - lastTime; // (timeNow - lastTime)*1000 / SDL_GetPerformanceFrequency();
			lastTime = timeNow;

			glfwPollEvents();

			if (m_Scene->GetCamera() == nullptr)
			{
				LOG_CORE_ERROR("Camera is not initialized!");
				break;
			}

			m_Scene->GetCamera()->HandleKeys(m_MainWindow->GetKeys(), deltaTime);
			m_Scene->GetCamera()->HandleMouse(m_MainWindow->GetMouseDeltaX(), m_MainWindow->GetMouseDeltaY());


			m_Scene->Update(deltaTime);
			directionalShadowPass(m_Scene->getDirectionalLight());
			omniShadowPass();
			renderPass(projection);

			m_MainWindow->SwapBuffers();
		}
	}

	void Engine::Stop()
	{

	}

	void Engine::renderPass(glm::mat4 projectionMatrix)
	{
		glViewport(0, 0, 1366, 768);
		//Clear window
		glm::vec3 backgroundColor = m_Scene->GetBackgroundColor();
		glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		if (m_Scene->UseSkyboxActive() && m_Scene->GetSkybox() != NULL)
		{
			m_Scene->GetSkybox()->DrawSkybox(m_Scene->GetCamera()->CalculateViewMatrix(), projectionMatrix);
		}

		m_Scene->SetPointLights();  //Use Shader
		m_Scene->SetSpotLights();
		m_Scene->RenderScene(projectionMatrix);
	}

	void Engine::directionalShadowPass(DirectionalLight* dLight)
	{
		glViewport(0, 0, dLight->GetShadowMap()->GetShadowWidth(), dLight->GetShadowMap()->GetShadowHeight());
		dLight->GetShadowMap()->Write();
		glClear(GL_DEPTH_BUFFER_BIT);

		m_Scene->RenderSceneShadowMap();
	}

	void Engine::omniShadowPass()
	{
		m_Scene->RenderSceneOmniShadowMap();
	}
}