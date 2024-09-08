#pragma once
#include "Core.h"
#include "CameraTypeEnum.h"
#include "Log.h"
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <GLFW\glfw3.h>
namespace GameEngine
{
	//TODO: abstract camera class ortho-perspective child classes
	class ENGINE_API Camera
	{
	public:
		Camera();
		Camera(glm::vec3 startPosition, glm::vec3 startUpVector, GLfloat startYawVal, GLfloat startPitchVal, GLfloat startMoveSpeed, GLfloat startRotateSpeed, float fov, float nearValue, float farValue, CameraType type);
		void HandleMouse(GLfloat mouseDeltaX, GLfloat mouseDeltaY);

		glm::vec3 GetCameraPosition();

		glm::mat4 CalculateViewMatrix();
		void MoveForward(float value);
		void MoveBack(float value);
		void MoveRight(float value);
		void MoveLeft(float value);

		glm::mat4 CalcGetProjectionMatrix(GLfloat aspectRatio);
		~Camera();

	private:
		glm::vec3 m_Position;
		glm::vec3 m_Front;
		glm::vec3 m_Up;
		glm::vec3 m_Right;
		glm::vec3 m_WorldUp;

		GLfloat m_Pitch;  //looking up-down
		GLfloat m_Yaw; //looking right-left

		GLfloat m_MoveSpeed;
		GLfloat m_RotateSpeed;

		CameraType m_Type;
		float m_Fov;
		float m_NearPlane;
		float m_FarPlane;
		glm::mat4 m_Projection;
		void update();
	};
}
