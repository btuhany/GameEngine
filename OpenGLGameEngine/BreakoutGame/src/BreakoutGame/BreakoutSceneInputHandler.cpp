#include "BreakoutSceneInputHandler.h"

void BreakoutSceneInputHandler::HandleKeys(int* keys, GLfloat deltaTime)
{
	if (keys[GLFW_KEY_1] == KEY_STATE_RELEASE)
	{
		OnPressedCameraTypeChangeKeyEvent.Trigger();
	}
}

void BreakoutSceneInputHandler::HandleMouse(GLfloat mouseDeltaX, GLfloat mouseDeltaY)
{
}
