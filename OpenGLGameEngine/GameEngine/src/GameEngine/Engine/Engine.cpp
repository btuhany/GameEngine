#define STB_IMAGE_IMPLEMENTATION
#include "Engine.h"

namespace GameEngine {
	Engine::Engine(Window* window, bool shadowPassActive)
	{
		m_MainWindow = window;
		m_IsInitialized = false;
		m_ShouldPause = false;
		m_ShadowPassActive = shadowPassActive;
	}

	Engine::Engine(Window* window, Input* input, bool shadowPassActive)
	{
		m_MainWindow = window;
		m_InputHandler = input;
		m_IsInitialized = false;
		m_ShouldPause = false;
		m_ShadowPassActive = shadowPassActive;
	}

	Engine::~Engine()
	{
		delete m_MainWindow;
		delete m_Renderer;
		delete m_CollisionManager;
	}

	void Engine::Initialize(Scene* scene, GameModeType gameModeType, bool activateCollisionSystem)
	{
		if (activateCollisionSystem)
		{
			m_CollisionManager = new CollisionManager();
		}

		m_GameModeType = gameModeType;
		m_IsCollisionsEnabled = activateCollisionSystem;
		m_Renderer = new Renderer();
		m_Scene = scene;


		m_MainWindow->Initialize();
		m_Scene->Initialize(m_MainWindow->getWidth(), m_MainWindow->getHeight());
		m_Renderer->PreInitialize(gameModeType);
		m_Renderer->Initialize(m_Scene, m_MainWindow->getBufferRatio(), m_MainWindow->getWidth(), m_MainWindow->getHeight());

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
		m_Renderer->Start();
		if (m_Scene->getCamera() == nullptr)
		{
			LOG_CORE_ERROR("Camera is not initialized!");
			m_ShouldPause = true;
		}
	}


	void Engine::Run()
	{
		if (m_ShouldPause)
			return;

		GLfloat deltaTime = 0.0f;
		GLfloat lastTime = 0.0f;
		const float targetFPS = 144.0f;
		const float targetFrameDurationSec = 1.0f / targetFPS;


		bool renderDirLightShadow = checkValidateDirLightShadowRendering(m_GameModeType);
		bool renderOmniLightShadow = checkValidateOmniLightShadowRendering(m_GameModeType);
		bool handleInputs = checkValidateInputHandler();

		
		while (!m_MainWindow->GetShouldClose())
		{
			if (m_ShouldPause)
				continue; //break;

			GLfloat timeNow = glfwGetTime(); //SDL_GetPerformanceCounter();
			deltaTime = timeNow - lastTime; // (timeNow - lastTime)*1000 / SDL_GetPerformanceFrequency();
			lastTime = timeNow;
			
			m_Scene->Update(deltaTime);

			glfwPollEvents();

			//TODO
			if (m_MainWindow->GetKeys()[GLFW_KEY_0] == KEY_STATE_RELEASE)
			{
				m_DebugInputActive = !m_DebugInputActive;
			}

			if (handleInputs)
			{
				if (m_DebugInputActive)
				{
					m_Scene->getCamera()->HandleMouse(m_MainWindow->GetMouseDeltaX(), m_MainWindow->GetMouseDeltaY());
					m_Scene->getCamera()->HandleKeys(m_MainWindow->GetKeys(), deltaTime);
				}
				else
				{
					m_InputHandler->HandleKeys(m_MainWindow->GetKeys(), deltaTime);
				}
			}

			if (m_IsCollisionsEnabled)
			{
				m_CollisionManager->Update(deltaTime);
			}

			//TODO one function
			m_Renderer->DrawScene(m_ShadowPassActive, renderDirLightShadow, renderOmniLightShadow);
			m_Renderer->DrawUI();

			m_MainWindow->SwapBuffers();
			m_MainWindow->ClearKeyCache();



			GLfloat frameTime = glfwGetTime() - timeNow;
			if (frameTime < targetFrameDurationSec)
			{
				std::this_thread::sleep_for(std::chrono::duration<float>(targetFrameDurationSec - frameTime));
			}
		}
	}

	void Engine::Pause()
	{
		m_ShouldPause = true;
	}
	void Engine::setDebugInputActive(bool active)
	{
		m_DebugInputActive = active;
	}
	bool Engine::checkValidateDirLightShadowRendering(GameModeType gameModeType)
	{
		bool renderDirLightShadow = false;
		if (gameModeType == GameModeType::ThreeDimensional)
		{
			std::shared_ptr<DirectionalLight> sceneDirLight = m_Scene->getDirectionalLight();
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
		}
		return renderDirLightShadow;
	}
	bool Engine::checkValidateOmniLightShadowRendering(GameModeType gameModeType)
	{
		bool renderOmniLightShadow = false;
		if (gameModeType == GameModeType::ThreeDimensional)
		{
			renderOmniLightShadow = m_Scene->IsOmniShadowShaderSet();
			if (!renderOmniLightShadow)
			{
				LOG_CORE_INFO("Omni light shadow shader is not set, make sure point and spot lights don't have shadow maps!");
			}
		}
		return renderOmniLightShadow;
	}
	bool Engine::checkValidateInputHandler()
	{
		bool handleInputs = true;
		if (m_InputHandler == nullptr)
		{
			LOG_CORE_INFO("Engine input handler is not set!");
			handleInputs = false;
		}
		return handleInputs;
	}
}