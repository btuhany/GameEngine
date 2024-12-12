#include "BreakoutSceneInputHandler.h"

void BreakoutSceneInputHandler::HandleKeys(int* keys, GLfloat deltaTime)
{
	if (keys[GLFW_KEY_1] == KEY_STATE_RELEASE)
	{
		OnPressedCameraTypeChangeKeyEvent.Trigger();
	}
	if (keys[GLFW_KEY_SPACE] == KEY_STATE_PRESS)
	{
		if (!m_IsSpaceButtonPressLocked)
		{
			m_IsSpaceButtonPressLocked = true;
			OnBallReleaseKeyEvent.Trigger();
		}
	}
	if (keys[GLFW_KEY_SPACE] == KEY_STATE_RELEASE)
	{
		m_IsSpaceButtonPressLocked = false;
	}
	if (keys[GLFW_KEY_LEFT] == KEY_STATE_PRESS || keys[GLFW_KEY_LEFT] == KEY_STATE_HELD)
	{
		OnLeftArrowKeyEvent.Trigger();
	}
	if (keys[GLFW_KEY_RIGHT] == KEY_STATE_PRESS || keys[GLFW_KEY_RIGHT] == KEY_STATE_HELD)
	{
		OnRightArrowKeyEvent.Trigger();
	}
	if (keys[GLFW_KEY_UP] == KEY_STATE_PRESS || keys[GLFW_KEY_UP] == KEY_STATE_HELD)
	{
		OnUpArrowKeyEvent.Trigger();
	}
	if (keys[GLFW_KEY_DOWN] == KEY_STATE_PRESS || keys[GLFW_KEY_DOWN] == KEY_STATE_HELD)
	{
		OnDownArrowKeyEvent.Trigger();
	}
	if (keys[GLFW_KEY_D] == KEY_STATE_RELEASE)
	{
		OnBallDebugKeyEvent.Trigger();
	}
}

void BreakoutSceneInputHandler::HandleMouse(GLfloat mouseDeltaX, GLfloat mouseDeltaY)
{
}
