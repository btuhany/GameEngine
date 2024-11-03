#include "BreakoutApp.h"

BreakoutApp::BreakoutApp()
{
}

BreakoutApp::~BreakoutApp()
{
}

void BreakoutApp::Run()
{
	GameEngine::Log::Init();
	BreakoutSceneInputHandler inputHandler = BreakoutSceneInputHandler();
	BreakoutGame::BreakoutScene breakoutScene = BreakoutGame::BreakoutScene(&inputHandler);

	GameEngine::Engine engine = GameEngine::Engine(new Window(1920, 1080, "Breakout"), &inputHandler, true);
	engine.Initialize(&breakoutScene, true);
	engine.setDebugInputActive(false);
	engine.Start();
	engine.Run(GameModeType::TwoDimensional);
}

GameEngine::Application* GameEngine::CreateApplication()
{
	return new BreakoutApp();
}