#include "DemoApp.h"

DemoApp::DemoApp()
{

}

DemoApp::~DemoApp() 
{

}

void DemoApp::Run()
{
	GameEngine::Log::Init();
	DemoSceneInputHandler inputHandler = DemoSceneInputHandler();
	DemoScene3D demoScene = DemoScene3D(&inputHandler);

	GameEngine::Engine engine = GameEngine::Engine(new Window(1920, 1080, "DemoApp"), &inputHandler, true);
	engine.Initialize(&demoScene);
	engine.setDebugInputActive(false);
	engine.Start();
	engine.Run(GameModeType::ThreeDimensional);
}

GameEngine::Application* GameEngine::CreateApplication()
{
	return new DemoApp();
}


