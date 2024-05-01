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
	void setCamera(Camera camera);
protected:
	void renderScene(glm::mat4 projection);
private:
	Camera m_MainCamera;
	std::vector<RenderableObject*> m_ObjectList;
	void updateObjects();
	void startObjects();
};

