#pragma once
#include "../Core.h"
#include "Window.h"
#include <GLFW\glfw3.h>
namespace GameEngine
{
	class ENGINE_API Input
	{
	public:
		Input();
		~Input();
		virtual void HandleKeys(int* keys, GLfloat deltaTime);
		virtual void HandleMouse(GLfloat mouseDeltaX, GLfloat mouseDeltaY);
	};
}

