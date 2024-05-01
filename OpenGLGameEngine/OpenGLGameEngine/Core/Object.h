#pragma once
#include "Renderer.h"

class Object
{
public:
	Object();
	~Object();
	Object(Renderer* renderer);
	void Start();
	void Tick();
	void RenderUpdate(glm::mat4 projectionMatrix, glm::mat4 viewMatrix, Camera* mainCamera);
	void TranslateTransform(glm::vec3 translateVector);
	void RotateTransform(float angle, glm::vec3 rotateVector);
	void ScaleTransform(glm::vec3 scaleVector);
private:
	Renderer* m_Renderer;
	Shader* m_Shader;
	glm::mat4 m_TransformModelMatrix;
};

