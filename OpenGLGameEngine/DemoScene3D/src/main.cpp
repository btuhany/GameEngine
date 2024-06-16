#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include <GameEngine.h>
#include "DemoScene3D/DemoScene3D.h"

int main()
{
	DemoScene3D scene;
	Engine engine = Engine(new Window(1366, 768));
	engine.Initialize(&scene);
	engine.Start();
	engine.Run();

	return 0;

}