#pragma once
#include "EntryPoint.h"
#include "GameEngine.h"
class BreakoutApp : public Application
{
public:
	BreakoutApp();
	~BreakoutApp();
	virtual void Run() override;
};

