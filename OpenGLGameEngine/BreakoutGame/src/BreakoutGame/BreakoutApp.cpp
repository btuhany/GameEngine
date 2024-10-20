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
	BreakoutScene breakoutScene = BreakoutScene(&inputHandler);

	GameEngine::Engine engine = GameEngine::Engine(new Window(1920, 1080, "Breakout"), &inputHandler, true);
	engine.Initialize(&breakoutScene);
	engine.setDebugInputActive(false);
	engine.Start();
	engine.Run(GameModeType::TwoDimensional);
}

GameEngine::Application* GameEngine::CreateApplication()
{
	return new BreakoutApp();
}