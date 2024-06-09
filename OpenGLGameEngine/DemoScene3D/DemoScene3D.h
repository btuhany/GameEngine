#pragma once
#include "Core/Scene.h"
#include "Core/Shader.h"

class DemoScene3D : public Scene
{
public:
	DemoScene3D();
	~DemoScene3D();
	void Initialize() override;
	void Start() override;
	void Update(GLfloat deltaTime) override;
private:
	Mesh* createCubeMesh();
	Mesh* createPlainMesh();

	Model* helicopterModelData;
	RenderableData* helicopterRenderableData;
	RenderableObject* helicopter;

	Model* ironmanModelData;
	RenderableData* ironmanRenderableData;
	RenderableObject* ironman;

	Renderer mainRenderer;

	Texture* spidermanTexture;
	Texture* plainTexture;

	Material shinyMaterial;
	Material roughMaterial;
	Shader* m_Shader;


	RenderableObject* spidermanPlain;
	RenderableObject* spidermanCube;
	void initializeSkybox();
};

