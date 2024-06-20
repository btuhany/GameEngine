#pragma once
#include <GameEngine.h>

class BreakoutScene : public Scene
{
public:
	BreakoutScene();
	~BreakoutScene();
	void Initialize() override;
	void Start() override;
	void Update(GLfloat deltaTime) override;
};

