#pragma once
#include <GLFW\glfw3.h>
namespace GameEngine
{
	class Input
	{
	public:
		Input();
		~Input();
		virtual void HandleKeys(bool* keys, GLfloat deltaTime);
		virtual void HandleMouse(GLfloat mouseDeltaX, GLfloat mouseDeltaY);
	};
}

