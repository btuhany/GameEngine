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
	void Update(glm::mat4 projection, GLfloat deltaTime) override;
private:
	Mesh* createCubeMesh();
	Renderer shinyRenderer;

	Model ironmanModel;

	Texture spidermanTexture;
	Texture plainTexture;

	Material shinyMaterial;
	Material roughMaterial;

	RenderableData helicopterRenderableData;
	Shader shader;
};

