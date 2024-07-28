#pragma once
#include "Core.h"
#include <stdio.h>
#include <iostream>
#include "Scene.h"
#include "Window.h"
#include "Camera.h"
#include "Log.h"
#include "Input.h"

namespace GameEngine {
	class ENGINE_API Engine
	{
	public:
		Engine(Window* window);
		Engine(Window* window, Input* input);
		~Engine();
		void Initialize(Scene* scene);
		void Start();
		void Run();
		void Stop();
	private:
		void renderPass(glm::mat4 projectionMatrix);
		void directionalShadowPass(DirectionalLight* dLight);
		void omniShadowPass();
		Window* m_MainWindow;
		Scene* m_Scene;
		Input* m_InputHandler;
		bool m_IsInitialized;
		bool m_ShouldStop;
	};
}
