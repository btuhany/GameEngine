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
	RenderableObject helicopter;
	RenderableObject ironman;
	RenderableObject spidermanPlain;
	RenderableObject spidermanCube;
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

