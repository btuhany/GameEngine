#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <GLFW\glfw3.h>


class Camera
{
public:
	Camera();
	Camera(glm::vec3 startPosition, glm::vec3 startUpVector, GLfloat startYawVal, GLfloat startPitchVal, GLfloat startMoveSpeed, GLfloat startRotateSpeed);

	void HandleKeys(bool* keys, GLfloat deltaTime);
	void HandleMouse(GLfloat mouseDeltaX, GLfloat mouseDeltaY);

	glm::vec3 GetCameraPosition();

	glm::mat4 CalculateViewMatrix();

	~Camera();

private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	GLfloat pitch;  //looking up-down
	GLfloat yaw; //looking right-left

	GLfloat moveSpeed;
	GLfloat rotateSpeed;

	void update();
};

