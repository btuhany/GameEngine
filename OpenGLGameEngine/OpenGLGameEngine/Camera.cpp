#include "Camera.h"

Camera::Camera()
{
}

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUpVector, GLfloat startYawVal, GLfloat startPitchVal, GLfloat startMoveSpeed, GLfloat startRotateSpeed)
{
	position = startPosition;
	worldUp = startUpVector;
	yaw = startYawVal;
	pitch = startPitchVal;
	front = glm::vec3(0.0f, 0.0f, -1.0f);

	moveSpeed = startMoveSpeed;
	rotateSpeed = startRotateSpeed;

	update();
}

void Camera::HandleKeys(bool* keys, GLfloat deltaTime)
{
	if (keys[GLFW_KEY_W])
	{
		position += front * moveSpeed * deltaTime;
	}
	if (keys[GLFW_KEY_D])
	{
		position += right * moveSpeed * deltaTime;
	}
	if (keys[GLFW_KEY_A])
	{
		position -= right * moveSpeed * deltaTime;
	}
	if (keys[GLFW_KEY_S])
	{
		position -= front * moveSpeed * deltaTime;
	}
}

void Camera::HandleMouse(GLfloat mouseDeltaX, GLfloat mouseDeltaY)
{
	mouseDeltaX *= rotateSpeed;
	mouseDeltaY *= rotateSpeed;
	
	yaw += mouseDeltaX;
	pitch += mouseDeltaY;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}
	else if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	update();
}

glm::mat4 Camera::CalculateViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

Camera::~Camera()
{
}

void Camera::update()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	//we need right vector first
	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}



