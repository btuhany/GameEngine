#include "DemoSceneInputHandler.h"

DemoSceneInputHandler::DemoSceneInputHandler()
{
}

DemoSceneInputHandler::~DemoSceneInputHandler()
{
}

void DemoSceneInputHandler::HandleKeys(int* keys, GLfloat deltaTime)
{
	if (keys[GLFW_KEY_LEFT_SHIFT] == KEY_STATE_PRESS || keys[GLFW_KEY_LEFT_SHIFT] == KEY_STATE_RELEASE)
	{
		OnPressedShiftEvent.Trigger(keys[GLFW_KEY_LEFT_SHIFT]);
	}
	if (keys[GLFW_KEY_W] == KEY_STATE_PRESS || keys[GLFW_KEY_W] == KEY_STATE_HELD)
	{
		OnPresssedUpEvent.Trigger();
	}
	if (keys[GLFW_KEY_D] == KEY_STATE_PRESS || keys[GLFW_KEY_D] == KEY_STATE_HELD)
	{
		OnPresssedRightEvent.Trigger();
	}
	if (keys[GLFW_KEY_A] == KEY_STATE_PRESS || keys[GLFW_KEY_A] == KEY_STATE_HELD)
	{
		OnPresssedLeftEvent.Trigger();
	}
	if (keys[GLFW_KEY_S] == KEY_STATE_PRESS || keys[GLFW_KEY_S] == KEY_STATE_HELD)
	{
		OnPresssedDownEvent.Trigger();
	}
	if (keys[GLFW_KEY_SPACE] == KEY_STATE_RELEASE)
	{
		OnPressedSpaceEvent.Trigger();
	}
}

void DemoSceneInputHandler::HandleMouse(GLfloat mouseDeltaX, GLfloat mouseDeltaY)
{
}
