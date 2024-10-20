#pragma once
#include <GameEngine.h>
#include "EntryPoint.h"
#include "BreakoutScene.h"
#include "BreakoutSceneInputHandler.h"
class BreakoutApp : public Application
{
public:
	BreakoutApp();
	~BreakoutApp();
	virtual void Run() override;
};

