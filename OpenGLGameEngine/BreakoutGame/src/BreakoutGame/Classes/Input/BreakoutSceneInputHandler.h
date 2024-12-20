#pragma once
#include <GameEngine.h>
#include "../Data/InputTypeEnum.h"
class BreakoutSceneInputHandler : public Input
{
/// <summary>
/// SPACE -> OnBallReleaseKeyEvent
/// </summary>
public:
	SimpleEvent<> OnPressedCameraTypeChangeKeyEvent;
	SimpleEvent<> OnLeftArrowKeyEvent;
	SimpleEvent<> OnRightArrowKeyEvent;
	SimpleEvent<> OnUpArrowKeyEvent;
	SimpleEvent<> OnDownArrowKeyEvent;
	SimpleEvent<> OnBallDebugKeyEvent;
	SimpleEvent<> OnBallReleaseKeyEvent;
	void HandleKeys(int* keys, GLfloat deltaTime) override;
	void HandleMouse(GLfloat mouseDeltaX, GLfloat mouseDeltaY) override;
	std::function<void(BreakoutGame::InputType)> onInputCallback;
private:
	void ProcessInputCallback(BreakoutGame::InputType inputType);
	bool m_IsSpaceButtonPressLocked = false;

};

