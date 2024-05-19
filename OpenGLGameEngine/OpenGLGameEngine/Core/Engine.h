#pragma once
#include <stdio.h>
#include <iostream>

#include "Scene.h"
#include "Window.h"
#include "Camera.h"

class Engine
{
public:
	Engine(Window* window);
	~Engine();
	void Initialize(Scene* scene);
	void Start();
	void Run();
	void Stop();
private:
	void renderPass(glm::mat4 projectionMatrix);
	Window* m_MainWindow;
	Scene* m_Scene;
	bool m_IsInitialized;
};

