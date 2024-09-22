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
		m_Scene = nullptr;
		delete m_Renderer;
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

		if (m_Scene->GetCamera() == nullptr)
		{
			LOG_CORE_ERROR("Camera is not initialized!");
			m_ShouldStop = true;
		}
	}

	void Engine::Run()
	{
		m_Renderer = new Renderer(m_Scene->GetSkybox(), m_Scene->GetBackgroundColor(), m_Scene->GetCamera());
		m_Renderer->RenderableMeshEntitiesPublic = m_Scene->RenderableMeshEntitiesPublic;
		m_Renderer->RenderableModelEntitiesPublic = m_Scene->RenderableModelEntitiesPublic;

		if (m_ShouldStop)
			return;

		GLfloat deltaTime = 0.0f;
		GLfloat lastTime = 0.0f;
		glm::mat4 projection = m_Scene->GetCamera()->CalcGetProjectionMatrix((GLfloat)m_MainWindow->GetBufferWidth() / m_MainWindow->GetBufferHeight());

		DirectionalLight* sceneDirLight = m_Scene->GetDirectionalLight();

		bool renderDirLightShadow;
		if (sceneDirLight == nullptr)
		{
			LOG_CORE_ERROR("Directional light is not set");
			renderDirLightShadow = false;
		}
		else
		{
			renderDirLightShadow = sceneDirLight->GetShadowMap() != nullptr;
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
			m_Scene->GetCamera()->HandleMouse(m_MainWindow->GetMouseDeltaX(), m_MainWindow->GetMouseDeltaY());

			if (m_ShadowPassActive)
			{
				if (renderDirLightShadow)
					m_Renderer->directionalShadowMapPass(m_Scene->GetDirectionalLight());
				if (renderOmniLightShadow)
					m_Renderer->omniShadowMapPass(m_Scene->m_OmniShadowShader, m_Scene->m_PointLightList, m_Scene->GetPointLightCount(),
						m_Scene->m_SpotLightList, m_Scene->m_SpotLightCount);
			}
			m_Renderer->renderPass(projection, m_Scene->m_PointLightList, m_Scene->GetPointLightCount(),
				m_Scene->m_SpotLightList, m_Scene->m_SpotLightCount);

			m_MainWindow->SwapBuffers();
		}
	}

	void Engine::Stop()
	{
		m_ShouldStop = true;
	}

	void Engine::renderPass(glm::mat4 projectionMatrix)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, 1366, 768);
		//Clear window
		glm::vec3 backgroundColor = m_Scene->GetBackgroundColor();
		glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		if (m_Scene->UseSkyboxActive() && m_Scene->GetSkybox() != nullptr)
		{
			m_Scene->GetSkybox()->DrawSkybox(m_Scene->GetCamera()->CalculateViewMatrix(), projectionMatrix);
		}

		if (m_Scene->GetPointLightCount() > 0)
		{
			m_Scene->SetPointLights();  //Use Shader
		}
		if (m_Scene->GetSpotLightCount() > 0)
		{
			m_Scene->SetSpotLights();
		}
		m_Scene->RenderScene(projectionMatrix);
	}

	void Engine::directionalShadowPass(DirectionalLight* dLight)
	{
		if (dLight == nullptr)
		{
			LOG_CORE_WARN("Directional light not initialized!");
			return;
		}

		if (dLight->GetShadowMap() == nullptr)
		{
			LOG_CORE_WARN("Directional light has no shadow map");
			return;
		}

		glViewport(0, 0, dLight->GetShadowMap()->GetShadowWidth(), dLight->GetShadowMap()->GetShadowHeight());
		dLight->GetShadowMap()->Write();
		glClear(GL_DEPTH_BUFFER_BIT);

		m_Scene->RenderSceneShadowMap();
	}

	void Engine::omniShadowPass()
	{
		if (m_Scene->GetPointLightCount() + m_Scene->GetSpotLightCount() == 0)
		{
			LOG_CORE_WARN("There aren't any lights to render omni shadows!");
			return;
		}
		m_Scene->RenderSceneOmniShadowMap();
	}
}