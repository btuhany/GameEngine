#pragma  once
#include <stdio.h>
#include "Scene.h"
#include "Log.h"
#include "Engine.h"

#ifdef GAME_ENGINE_WINDOWS

extern GameEngine::Scene* GameEngine::CreateScene();

int main(int argc, char** argv)
{
	GameEngine::Log::Init();
	GameEngine::Engine engine = GameEngine::Engine(new GameEngine::Window(1366, 768));
	auto scene = GameEngine::CreateScene();
	engine.Initialize(scene);
	engine.Start();
	engine.Run();

	return 0;
}

#endif 