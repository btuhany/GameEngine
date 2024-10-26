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
		OnShiftKeyEvent.Trigger(keys[GLFW_KEY_LEFT_SHIFT]);
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
	if (keys[GLFW_KEY_SPACE] == KEY_STATE_PRESS || keys[GLFW_KEY_SPACE] == KEY_STATE_HELD)
	{
		OnPressedSpaceEvent.Trigger();
	}
	if (keys[GLFW_KEY_LEFT_CONTROL] == KEY_STATE_PRESS || keys[GLFW_KEY_LEFT_CONTROL] == KEY_STATE_HELD)
	{
		OnPressedCtrlEvent.Trigger();
	}
	if (keys[GLFW_KEY_C] == KEY_STATE_RELEASE)
	{
		OnEnableDisableKeyEvent.Trigger();
	}
	if (keys[GLFW_KEY_Q] == KEY_STATE_PRESS || keys[GLFW_KEY_Q] == KEY_STATE_HELD)
	{
		OnPressedRotateLeftKeyEvent.Trigger();
	}
	if (keys[GLFW_KEY_E] == KEY_STATE_PRESS || keys[GLFW_KEY_E] == KEY_STATE_HELD)
	{
		OnPressedRotateRightKeyEvent.Trigger();
	}
	if (keys[GLFW_KEY_P] == KEY_STATE_RELEASE)
	{
		OnPauseKeyEvent.Trigger();
	}
	if (keys[GLFW_KEY_N] == KEY_STATE_RELEASE)
	{
		OnShaderChangeKeyEvent.Trigger();
	}
	if (keys[GLFW_KEY_RIGHT] == KEY_STATE_RELEASE)
	{
		OnSelectRightObjectKeyEvent.Trigger();
	}
	if (keys[GLFW_KEY_LEFT] == KEY_STATE_RELEASE)
	{
		OnSelectLeftObjectKeyEvent.Trigger();
	}
	if (keys[GLFW_KEY_J] == KEY_STATE_PRESS || keys[GLFW_KEY_J] == KEY_STATE_HELD)
	{
		OnScaleUpKeyEvent.Trigger();
	}
	if (keys[GLFW_KEY_K] == KEY_STATE_PRESS || keys[GLFW_KEY_K] == KEY_STATE_HELD)
	{
		OnScaleDownKeyEvent.Trigger();
	}
}

void DemoSceneInputHandler::HandleMouse(GLfloat mouseDeltaX, GLfloat mouseDeltaY)
{
}
