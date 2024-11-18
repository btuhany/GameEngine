#pragma once
#include <memory.h>
#include "../Core.h"
#include <stdio.h>
#include <iostream>
#include "../Scene/Scene.h"
#include "Window.h"
#include "../Scene/Camera.h"
#include "../Debugging/Log.h"
#include "Input.h"
#include "../Scene/CameraTypeEnum.h"
#include "../Render/Renderer.h"
#include "../Collision/CollisionManager.h"
#include "../Render/TextRenderManager.h"

namespace GameEngine {
	enum class GameModeType
	{
		TwoDimensional = 0,
		ThreeDimensional
	};

	class ENGINE_API Engine
	{
	public:
		Engine(Window* window, bool shadowPassActive);
		Engine(Window* window, Input* input, bool shadowPassActive);
		~Engine();
		void Initialize(Scene* scene, GameModeType gameModeType, bool activateCollisionSystem = false);
		void Start();
		void Run();
		void Pause();
		void setDebugInputActive(bool active);
	private:
		Window* m_MainWindow = nullptr;
		Scene* m_Scene = nullptr;
		Input* m_InputHandler = nullptr;
		Renderer* m_Renderer = nullptr;
		CollisionManager* m_CollisionManager = nullptr;
		GameModeType m_GameModeType;
		bool m_IsInitialized;
		bool m_ShouldPause;
		bool m_ShadowPassActive;
		bool m_DebugInputActive;
		bool m_IsCollisionsEnabled;
		bool checkValidateDirLightShadowRendering(GameModeType gameModeType);
		bool checkValidateOmniLightShadowRendering(GameModeType gameModeType);
		bool checkValidateInputHandler();
	};
}
