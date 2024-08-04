#pragma once
#include <GameEngine.h>
#include "DemoSceneInputHandler.h"

class DemoScene3D : public Scene
{
public:
	DemoScene3D();
	DemoScene3D(DemoSceneInputHandler* input);
	~DemoScene3D();
	void Initialize() override;
	void Start() override;
	void Update(GLfloat deltaTime) override;
private:
	void initializeSkybox();
	Mesh* createCubeMesh();
	Mesh* createPlainMesh();
	Renderable3DObject helicopter;
	Renderable3DObject ironman;
	Renderable3DObject spidermanPlain;
	Renderable3DObject spidermanCube;
	void handleOnRightKey();
	void handleOnLeftKey();
	void handleOnUpKey();
	void handleOnDownKey();
	void handleOnShiftKey();
	void handleOnShiftReleasedKey();
	DemoSceneInputHandler* m_InputReader;
	float m_CameraSpeed;
	float m_DeltaTime;
};

