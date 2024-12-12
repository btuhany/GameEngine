#pragma once
#include <GameEngine.h>
#include "EntryPoint.h"
#include "../Scene/BreakoutScene.h"
#include "../Input/BreakoutSceneInputHandler.h"
class BreakoutApp : public Application
{
public:
	BreakoutApp();
	~BreakoutApp();
	virtual void Run() override;
};

