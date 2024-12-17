#include "BreakoutSceneInputHandler.h"

void BreakoutSceneInputHandler::HandleKeys(int* keys, GLfloat deltaTime)
{
	if (keys[GLFW_KEY_D] == KEY_STATE_RELEASE)
	{
		ProcessInputCallback(BreakoutGame::InputType::DebugKey_ChangeControlledObject);
		OnBallDebugKeyEvent.Trigger();
	}

	if (!IsPlayerControlsActive)
		return;

	if (keys[GLFW_KEY_1] == KEY_STATE_RELEASE)
	{
		ProcessInputCallback(BreakoutGame::InputType::DebugKey_ChangeCamera);
		OnPressedCameraTypeChangeKeyEvent.Trigger();
	}
	if (keys[GLFW_KEY_SPACE] == KEY_STATE_PRESS)
	{
		if (!m_IsSpaceButtonPressLocked)
		{
			ProcessInputCallback(BreakoutGame::InputType::SpaceKey);
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
		ProcessInputCallback(BreakoutGame::InputType::LeftArrow);
		OnLeftArrowKeyEvent.Trigger();
	}
	if (keys[GLFW_KEY_RIGHT] == KEY_STATE_PRESS || keys[GLFW_KEY_RIGHT] == KEY_STATE_HELD)
	{
		ProcessInputCallback(BreakoutGame::InputType::RightArrow);
		OnRightArrowKeyEvent.Trigger();
	}
	if (keys[GLFW_KEY_UP] == KEY_STATE_PRESS || keys[GLFW_KEY_UP] == KEY_STATE_HELD)
	{
		ProcessInputCallback(BreakoutGame::InputType::UpArrow);
		OnUpArrowKeyEvent.Trigger();
	}
	if (keys[GLFW_KEY_DOWN] == KEY_STATE_PRESS || keys[GLFW_KEY_DOWN] == KEY_STATE_HELD)
	{
		ProcessInputCallback(BreakoutGame::InputType::DownArrow);
		OnDownArrowKeyEvent.Trigger();
	}
}

void BreakoutSceneInputHandler::HandleMouse(GLfloat mouseDeltaX, GLfloat mouseDeltaY)
{
}

void BreakoutSceneInputHandler::ProcessInputCallback(BreakoutGame::InputType inputType)
{
	if (onInputCallback)
	{
		onInputCallback(inputType);
	}
}
