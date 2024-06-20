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
	GameEngine::Engine engine = GameEngine::Engine(new GameEngine::Window(1366, 768, "DemoApp"));
	printf("demo");
	//engine.Initialize(new DemoScene3D());
	//engine.Start();
	//engine.Run();
}

GameEngine::Application* GameEngine::CreateApplication()
{
	return new DemoApp();
}


