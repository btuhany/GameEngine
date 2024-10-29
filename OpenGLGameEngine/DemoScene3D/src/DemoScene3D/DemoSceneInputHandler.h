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
	SimpleEvent<> OnDestroyKeyEvent;
	SimpleEvent<> OnPressedRotateLeftKeyEvent;
	SimpleEvent<> OnPressedRotateRightKeyEvent;
	SimpleEvent<> OnPauseKeyEvent;
	SimpleEvent<> OnShaderChangeKeyEvent;
	SimpleEvent<> OnSelectRightObjectKeyEvent;
	SimpleEvent<> OnSelectLeftObjectKeyEvent;
	SimpleEvent<> OnScaleUpKeyEvent;
	SimpleEvent<> OnScaleDownKeyEvent;
	void HandleKeys(int* keys, GLfloat deltaTime) override;
	void HandleMouse(GLfloat mouseDeltaX, GLfloat mouseDeltaY) override;
};

