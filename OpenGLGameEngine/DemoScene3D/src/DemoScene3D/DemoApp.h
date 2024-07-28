#pragma once
#include "GameEngine.h"
#include "EntryPoint.h"
#include "DemoScene3D.h"
#include "DemoSceneInputHandler.h"
class DemoApp : public Application
{
public:
	DemoApp();
	~DemoApp();
	virtual void Run() override;
};

