#pragma once
#include "Core/Scene.h"
class DemoScene3D : public Scene
{
public:
	DemoScene3D();
	~DemoScene3D();
	void Initialize() override;
	void Start() override;
	void Update(glm::mat4 projection, GLfloat deltaTime) override;
};

