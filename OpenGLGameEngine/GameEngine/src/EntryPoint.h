#pragma  once
#include <stdio.h>
#include "GameEngine/Core/Application.h"

#ifdef GAME_ENGINE_WINDOWS

extern GameEngine::Application* GameEngine::CreateApplication();

int main(int argc, char** argv)
{
	auto app = GameEngine::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif