#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include "Core/Engine.h"
#include "Core/Camera.h"
#include "Core/RenderableObject.h"
#include "DemoScene3D.h"
#include "Core/RenderableData.h"
#include "Core/ConstantValues.h"




int main()
{
	DemoScene3D scene;
	Engine engine = Engine(new Window(1366, 768));
	engine.Initialize(&scene);
	engine.Start();
	engine.Run();

	return 0;

}