#pragma once
#include <GameEngine.h>

class DemoScene3D : public Scene
{
public:
	DemoScene3D();
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

};

