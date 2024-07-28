#include "BreakoutApp.h"

BreakoutApp::BreakoutApp()
{
}

BreakoutApp::~BreakoutApp()
{
}

void BreakoutApp::Run()
{
	//GameEngine::Log::Init();
	//GameEngine::Engine engine = GameEngine::Engine(new GameEngine::Window(1366, 768, "Breakout"));

	//engine.Initialize(new BreakoutScene());
	//engine.Start();
	//engine.Run();
}

GameEngine::Application* GameEngine::CreateApplication()
{
	return new BreakoutApp();
}