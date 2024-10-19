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
	SimpleEvent<int> OnShiftKeyEvent;
	SimpleEvent<> OnPressedSpaceEvent;
	SimpleEvent<> OnPressedCtrlEvent;
	SimpleEvent<> OnEnableDisableKeyEvent;
	SimpleEvent<> OnPressedRotateLeftKeyEvent;
	SimpleEvent<> OnPressedRotateRightKeyEvent;
	SimpleEvent<> OnPauseKeyEvent;
	SimpleEvent<> OnShaderChangeKeyEvent;
	void HandleKeys(int* keys, GLfloat deltaTime) override;
	void HandleMouse(GLfloat mouseDeltaX, GLfloat mouseDeltaY) override;

};

