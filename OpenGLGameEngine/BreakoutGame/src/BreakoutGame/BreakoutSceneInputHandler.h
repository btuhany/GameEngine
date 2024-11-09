#pragma once
#include <GameEngine.h>
class BreakoutSceneInputHandler : public Input
{
public:
	SimpleEvent<> OnPressedCameraTypeChangeKeyEvent;
	SimpleEvent<> OnLeftArrowKeyEvent;
	SimpleEvent<> OnRightArrowKeyEvent;
	SimpleEvent<> OnUpArrowKeyEvent;
	SimpleEvent<> OnDownArrowKeyEvent;
	SimpleEvent<> OnBallDebugKeyEvent;
	void HandleKeys(int* keys, GLfloat deltaTime) override;
	void HandleMouse(GLfloat mouseDeltaX, GLfloat mouseDeltaY) override;
};

