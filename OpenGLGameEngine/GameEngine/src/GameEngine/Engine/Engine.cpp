#define STB_IMAGE_IMPLEMENTATION
#include "Engine.h"

namespace GameEngine {
	Engine::Engine(Window* window, bool shadowPassActive)
	{
		m_MainWindow = window;
		m_IsInitialized = false;
		m_ShouldStop = false;
		m_ShadowPassActive = shadowPassActive;
	}

	Engine::Engine(Window* window, Input* input, bool shadowPassActive)
	{
		m_MainWindow = window;
		m_InputHandler = input;
		m_IsInitialized = false;
		m_ShouldStop = false;
		m_ShadowPassActive = shadowPassActive;

	}

	Engine::~Engine()
	{
		delete m_MainWindow;
		delete m_Renderer;
	}

	void Engine::Initialize(Scene* scene)
	{
		m_Renderer = new Renderer();
		m_Scene = scene;

		m_MainWindow->Initialize();
		m_Scene->Initialize();
		m_Renderer->Initialize(m_Scene);

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

		if (m_Scene->getCamera() == nullptr)
		{
			LOG_CORE_ERROR("Camera is not initialized!");
			m_ShouldStop = true;
		}
	}

	void Engine::Run()
	{
		if (m_ShouldStop)
			return;

		GLfloat deltaTime = 0.0f;
		GLfloat lastTime = 0.0f;
		glm::mat4 projection = m_Scene->getCamera()->CalcGetProjectionMatrix((GLfloat)m_MainWindow->GetBufferWidth() / m_MainWindow->GetBufferHeight());

		DirectionalLight* sceneDirLight = m_Scene->getDirectionalLight();

		bool renderDirLightShadow;
		if (sceneDirLight == nullptr)
		{
			LOG_CORE_ERROR("Directional light is not set");
			renderDirLightShadow = false;
		}
		else
		{
			renderDirLightShadow = sceneDirLight->getShadowMap() != nullptr;
		}

		if (!renderDirLightShadow)
		{
			LOG_CORE_INFO("Directional light has no shadow map, make sure correct dir light constructor (with shadowmaps) is used if you want to render dir light shadows!");
		}
		bool renderOmniLightShadow = m_Scene->IsOmniShadowShaderSet();
		if (!renderOmniLightShadow)
		{
			LOG_CORE_INFO("Omni light shadow shader is not set, make sure point and spot lights don't have shadow maps!");
		}

		bool handleInputs = true;
		if (m_InputHandler == nullptr)
		{
			LOG_CORE_INFO("Engine input handler is not set!");
			handleInputs = false;
		}
		

		while (!m_MainWindow->GetShouldClose())
		{
			if (m_ShouldStop)
				continue; //break;

			GLfloat timeNow = glfwGetTime(); //SDL_GetPerformanceCounter();
			deltaTime = timeNow - lastTime; // (timeNow - lastTime)*1000 / SDL_GetPerformanceFrequency();
			lastTime = timeNow;

			m_Scene->Update(deltaTime);

			glfwPollEvents();

			if (handleInputs)
				m_InputHandler->HandleKeys(m_MainWindow->GetKeys(), deltaTime);
			m_Scene->getCamera()->HandleMouse(m_MainWindow->GetMouseDeltaX(), m_MainWindow->GetMouseDeltaY());

			if (m_ShadowPassActive)
			{
				if (renderDirLightShadow)
					m_Renderer->DirectionalShadowMapPass(m_Scene->getDirectionalLight());
				if (renderOmniLightShadow)
					m_Renderer->OmniShadowMapPass(m_Scene->getOmniShadowShader(), m_Scene->m_PointLightList, m_Scene->getPointLightCount(),
						m_Scene->m_SpotLightList, m_Scene->m_SpotLightCount);
			}
			m_Renderer->RenderPass(projection, m_Scene->m_PointLightList, m_Scene->getPointLightCount(),
				m_Scene->m_SpotLightList, m_Scene->m_SpotLightCount);

			m_MainWindow->SwapBuffers();
		}
	}

	void Engine::Stop()
	{
		m_ShouldStop = true;
	}
}