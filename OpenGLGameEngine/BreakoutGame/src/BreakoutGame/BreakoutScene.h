#pragma once
#include <GameEngine.h>
#include "BreakoutSceneInputHandler.h"
class BreakoutScene : public Scene
{
public:
	BreakoutScene();
	BreakoutScene(BreakoutSceneInputHandler* inputHandler);
	~BreakoutScene();
	void Initialize() override;
	void Start() override;
	void Update(GLfloat deltaTime) override;
private:
	BreakoutSceneInputHandler* m_InputHandler;
	std::shared_ptr<MeshData> createCubeMeshData();
	void initializeInputCallbacks();
	void changeCameraType();
};

