#pragma once
#include <GameEngine.h>
#include "EntryPoint.h"
#include "BreakoutScene.h"
class BreakoutApp : public Application
{
public:
	BreakoutApp();
	~BreakoutApp();
	virtual void Run() override;
};

