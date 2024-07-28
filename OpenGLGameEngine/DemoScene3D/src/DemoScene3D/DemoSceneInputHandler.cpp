#include "DemoSceneInputHandler.h"

DemoSceneInputHandler::DemoSceneInputHandler()
{
}

DemoSceneInputHandler::~DemoSceneInputHandler()
{
}

void DemoSceneInputHandler::HandleKeys(bool* keys, GLfloat deltaTime)
{
	if (keys[GLFW_KEY_LEFT_SHIFT])
	{
		OnPressedShiftEvent.Trigger();
	}
	if (keys[GLFW_KEY_W])
	{
		OnPresssedUpEvent.Trigger();
	}
	if (keys[GLFW_KEY_D])
	{
		OnPresssedRightEvent.Trigger();
	}
	if (keys[GLFW_KEY_A])
	{
		OnPresssedLeftEvent.Trigger();
	}
	if (keys[GLFW_KEY_S])
	{
		OnPresssedDownEvent.Trigger();
	}
}

void DemoSceneInputHandler::HandleMouse(GLfloat mouseDeltaX, GLfloat mouseDeltaY)
{
}
