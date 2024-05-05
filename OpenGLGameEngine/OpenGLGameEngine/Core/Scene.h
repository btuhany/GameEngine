#pragma once
#include "Camera.h"
#include "Window.h"
#include <vector>
#include "RenderableObject.h"

class Scene
{
public:
	Scene();
	~Scene();
	virtual void Initialize();
	virtual void Start();
	virtual void Update(glm::mat4 projection, GLfloat deltaTime);
	void AddObject(RenderableObject* object);
	Camera* GetCamera();
protected:
	void renderScene(glm::mat4 projection);
	Camera* m_MainCamera;
private:
	std::vector<RenderableObject*> m_ObjectList;
	void updateObjects();
	void startObjects();
};

