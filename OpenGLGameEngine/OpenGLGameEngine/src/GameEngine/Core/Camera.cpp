#include "Camera.h"

Camera::Camera()
{
}

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUpVector, GLfloat startYawVal, GLfloat startPitchVal, GLfloat startMoveSpeed, GLfloat startRotateSpeed)
{
	m_Position = startPosition;
	m_WorldUp = startUpVector;
	m_Yaw = startYawVal;
	m_Pitch = startPitchVal;
	m_Front = glm::vec3(0.0f, 0.0f, -1.0f);

	m_MoveSpeed = startMoveSpeed;
	m_RotateSpeed = startRotateSpeed;

	update();
}

void Camera::HandleKeys(bool* keys, GLfloat deltaTime)
{
	GLfloat curMoveSpeed = m_MoveSpeed;

	if (keys[GLFW_KEY_LEFT_SHIFT])
	{
		curMoveSpeed *= 3.0f;
	}
	if (keys[GLFW_KEY_W])
	{
		m_Position += m_Front * curMoveSpeed * deltaTime;
	}
	if (keys[GLFW_KEY_D])
	{
		m_Position += m_Right * curMoveSpeed * deltaTime;
	}
	if (keys[GLFW_KEY_A])
	{
		m_Position -= m_Right * curMoveSpeed * deltaTime;
	}
	if (keys[GLFW_KEY_S])
	{
		m_Position -= m_Front * curMoveSpeed * deltaTime;
	}
}

void Camera::HandleMouse(GLfloat mouseDeltaX, GLfloat mouseDeltaY)
{
	mouseDeltaX *= m_RotateSpeed;
	mouseDeltaY *= m_RotateSpeed;

	m_Yaw += mouseDeltaX;
	m_Pitch += mouseDeltaY;
	if (m_Pitch > 89.0f)
	{
		m_Pitch = 89.0f;
	}
	else if (m_Pitch < -89.0f)
	{
		m_Pitch = -89.0f;
	}
	update();
}

glm::vec3 Camera::GetCameraPosition()
{
	return m_Position;
}

glm::mat4 Camera::CalculateViewMatrix()
{
	return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
}

Camera::~Camera()
{
}

void Camera::update()
{
	m_Front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_Front.y = sin(glm::radians(m_Pitch));
	m_Front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_Front = glm::normalize(m_Front);
	//we need right vector first
	m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
	m_Up = glm::normalize(glm::cross(m_Right, m_Front));

}
