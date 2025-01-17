#include "Camera.h"

namespace GameEngine {

	Camera::Camera()
	{
	}

	Camera::Camera(glm::vec3 startPosition, glm::vec3 startUpVector, GLfloat startYawVal, GLfloat startPitchVal, GLfloat startMoveSpeed, GLfloat startRotateSpeed, float fov, float nearValue, float farValue, CameraType type)
	{
		m_WorldUp = startUpVector;
		m_Yaw = startYawVal;
		m_Pitch = startPitchVal;
		m_Front = glm::vec3(0.0f, 0.0f, -1.0f);
		m_Position = startPosition;

		m_MoveSpeed = startMoveSpeed;
		m_RotateSpeed = startRotateSpeed;

		m_Fov = fov;
		m_NearPlane = nearValue;
		m_FarPlane = farValue;
		m_Type = type;
		update();
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

	void Camera::Rotate(float yawValue, float pitchValue)
	{
		m_Yaw += yawValue;
		m_Pitch += pitchValue;
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

	void Camera::HandleKeys(int* keys, GLfloat deltaTime)
	{
		if (keys[GLFW_KEY_LEFT_SHIFT] == KEY_STATE_PRESS)
		{
			m_MoveSpeed = 15.0f;
		}
		else if (keys[GLFW_KEY_LEFT_SHIFT] == KEY_STATE_RELEASE)
		{
			m_MoveSpeed = 5.0f;
		}
		if (keys[GLFW_KEY_W] == KEY_STATE_PRESS || keys[GLFW_KEY_W] == KEY_STATE_HELD)
		{
			MoveForward(m_MoveSpeed * deltaTime);
		}
		if (keys[GLFW_KEY_D] == KEY_STATE_PRESS || keys[GLFW_KEY_D] == KEY_STATE_HELD)
		{
			MoveRight(m_MoveSpeed * deltaTime);
		}
		if (keys[GLFW_KEY_A] == KEY_STATE_PRESS || keys[GLFW_KEY_A] == KEY_STATE_HELD)
		{
			MoveLeft(m_MoveSpeed * deltaTime);
		}
		if (keys[GLFW_KEY_S] == KEY_STATE_PRESS || keys[GLFW_KEY_S] == KEY_STATE_HELD)
		{
			MoveBack(m_MoveSpeed * deltaTime);
		}
		if (keys[GLFW_KEY_SPACE] == KEY_STATE_PRESS || keys[GLFW_KEY_SPACE] == KEY_STATE_HELD)
		{
			MoveUp(m_MoveSpeed * deltaTime);
		}
		if (keys[GLFW_KEY_LEFT_CONTROL] == KEY_STATE_PRESS || keys[GLFW_KEY_LEFT_CONTROL] == KEY_STATE_HELD)
		{
			MoveDown(m_MoveSpeed * deltaTime);
		}
		if (keys[GLFW_KEY_G] == KEY_STATE_RELEASE)
		{
			m_Position = glm::cross(m_WorldUp, glm::vec3(0.0f, 0.0f, -5.0f));
		}
	}

	glm::vec3 Camera::getPosition()
	{
		return m_Position;
	}

	float Camera::getYawValue()
	{
		return m_Yaw;
	}

	float Camera::getPitchValue()
	{
		return m_Pitch;
	}

	glm::mat4 Camera::CalculateViewMatrix()
	{
		return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
	}

	void Camera::MoveForward(float value)
	{
		m_Position += m_Front * value;
	}

	void Camera::MoveBack(float value)
	{
		m_Position -= m_Front * value;
	}

	void Camera::MoveRight(float value)
	{
		m_Position += m_Right * value;
	}

	void Camera::MoveLeft(float value)
	{
		m_Position -= m_Right * value;

	}

	void Camera::MoveUp(float value)
	{
		m_Position += m_Up * value;
	}

	void Camera::MoveDown(float value)
	{
		m_Position -= m_Up * value;
	}

	glm::mat4 Camera::CalcGetProjectionMatrix(GLfloat aspectRatio)
	{
		if (m_Type == CAMERA_TYPE_PERSPECTIVE)
		{
			m_Projection = glm::perspective(glm::radians(m_Fov), aspectRatio, m_NearPlane, m_FarPlane);
		}
		else if (m_Type == CAMERA_TYPE_ORTHOGONAL)
		{
			auto sceneWidth = m_Fov * aspectRatio;
			auto sceneHeight = m_Fov;
			m_Projection = glm::ortho(-(sceneWidth / 2), sceneWidth / 2, -(sceneHeight / 2), sceneHeight / 2, m_NearPlane, m_FarPlane);
		}
		else
		{
			LOG_CORE_ERROR("Camera type has not been set, projection matrix couldn't calculated");
		}
		return m_Projection;
	}

	CameraType Camera::getCameraType()
	{
		return m_Type;
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
}