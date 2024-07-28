#pragma once
#include <GameEngine.h>

class DemoSceneInputHandler : public Input
{
public:
	DemoSceneInputHandler();
	~DemoSceneInputHandler();

	SimpleEvent<> OnPresssedRightEvent;
	SimpleEvent<> OnPresssedLeftEvent;
	SimpleEvent<> OnPresssedUpEvent;
	SimpleEvent<> OnPresssedDownEvent;
	SimpleEvent<> OnPressedShiftEvent;
	SimpleEvent<> OnReleasedShiftEvent;
	void HandleKeys(int* keys, GLfloat deltaTime) override;
	void HandleMouse(GLfloat mouseDeltaX, GLfloat mouseDeltaY) override;

};

