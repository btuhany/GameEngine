#pragma once
#include <GameEngine.h>
class BreakoutSceneInputHandler : public Input
{
public:
	SimpleEvent<> OnPressedCameraTypeChangeKeyEvent;
	void HandleKeys(int* keys, GLfloat deltaTime) override;
	void HandleMouse(GLfloat mouseDeltaX, GLfloat mouseDeltaY) override;
};

