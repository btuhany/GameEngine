#pragma once
#include "Camera.h"
#include "Window.h"
#include "Skybox.h"
#include <vector>
#include "RenderableObject.h"

class Scene
{
public:
	Scene();
	~Scene();
	virtual void Initialize();
	virtual void Start();
	virtual void Update(GLfloat deltaTime);
	void AddObject(RenderableObject* object);
	Camera* GetCamera();
	Skybox* GetSkybox();
	glm::vec3 GetBackgroundColor();
	bool UseSkyboxActive();
	void RenderScene(glm::mat4 projection, bool useShaders);
protected:
	void setBackgroundColor(glm::vec3 colour);
	void setCamera(Camera* camera);
	void setSkybox(Skybox* skybox);
	void useSkybox(bool useSkybox);
private:
	std::vector<RenderableObject*> m_ObjectList;
	void updateObjects();
	void startObjects();
	glm::vec3 m_BackgroundColour = glm::vec3(0.0f, 0.0f, 0.0f);
	Camera* m_MainCamera;
	Skybox* m_Skybox;
	DirectionalLight* m_DirectionalLight;
	bool m_UseSkybox = false;
};

