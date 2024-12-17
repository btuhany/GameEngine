#include "BreakoutSceneInputHandler.h"

void BreakoutSceneInputHandler::HandleKeys(int* keys, GLfloat deltaTime)
{
	std::vector<BreakoutGame::InputType> inputList = std::vector<BreakoutGame::InputType>();
	if (keys[GLFW_KEY_D] == KEY_STATE_RELEASE)
	{
		inputList.push_back(BreakoutGame::InputType::DebugKey_ChangeControlledObject);
		OnBallDebugKeyEvent.Trigger();
	}

	if (!IsPlayerControlsActive)
		return;

	if (keys[GLFW_KEY_1] == KEY_STATE_RELEASE)
	{
		inputList.push_back(BreakoutGame::InputType::DebugKey_ChangeCamera);
		OnPressedCameraTypeChangeKeyEvent.Trigger();
	}
	if (keys[GLFW_KEY_SPACE] == KEY_STATE_PRESS)
	{
		if (!m_IsSpaceButtonPressLocked)
		{
			inputList.push_back(BreakoutGame::InputType::SpaceKey);
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
		inputList.push_back(BreakoutGame::InputType::LeftArrow);
		OnLeftArrowKeyEvent.Trigger();
	}
	if (keys[GLFW_KEY_RIGHT] == KEY_STATE_PRESS || keys[GLFW_KEY_RIGHT] == KEY_STATE_HELD)
	{
		inputList.push_back(BreakoutGame::InputType::RightArrow);
		OnRightArrowKeyEvent.Trigger();
	}
	if (keys[GLFW_KEY_UP] == KEY_STATE_PRESS || keys[GLFW_KEY_UP] == KEY_STATE_HELD)
	{
		inputList.push_back(BreakoutGame::InputType::UpArrow);
		OnUpArrowKeyEvent.Trigger();
	}
	if (keys[GLFW_KEY_DOWN] == KEY_STATE_PRESS || keys[GLFW_KEY_DOWN] == KEY_STATE_HELD)
	{
		inputList.push_back(BreakoutGame::InputType::DownArrow);
		OnDownArrowKeyEvent.Trigger();
	}

	if (onInputCallback)
	{
		for (size_t i = 0; i < inputList.size(); i++)
		{
			onInputCallback(inputList[i]);
		}
	}
}

void BreakoutSceneInputHandler::HandleMouse(GLfloat mouseDeltaX, GLfloat mouseDeltaY)
{
}
