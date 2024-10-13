#pragma once
#include "../Core.h"
#include <stdio.h>

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <vector>
namespace GameEngine {
	class ENGINE_API Window
	{
	public:
		Window();
		Window(GLint windowWidth, GLint windowHeight, const char* windowName);

		int Initialize();

		GLfloat GetBufferWidth() { return m_BufferWidth; }
		GLfloat GetBufferHeight() { return m_BufferHeight; }

		bool GetShouldClose() { return glfwWindowShouldClose(m_glWindow); }

		int* GetKeys() { return m_Keys; }
		GLfloat GetMouseDeltaX();
		GLfloat GetMouseDeltaY();

		void SwapBuffers() { glfwSwapBuffers(m_glWindow); }

		void ClearKeyCache();


		~Window();
	private:
		GLFWwindow* m_glWindow;

		GLint m_Width, m_Height;
		GLint m_BufferWidth, m_BufferHeight;

		int m_Keys[1024]; //covering the ascii characters
		std::vector<int> m_KeysCache; //to reset key states

		GLfloat m_MouseLastXPosition = 0;
		GLfloat m_MouseLastYPosition = 0;
		GLfloat m_MouseDeltaX = 0;
		GLfloat m_MouseDeltaY = 0;
		bool m_MouseFirstMoved = true;

		const char* m_WindowName;

		void createCallbacks();
		static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
		static void handleMouse(GLFWwindow* window, double xPos, double yPos);
	};

	enum KeyState {
		KEY_STATE_NONE = 0,
		KEY_STATE_PRESS = 1,
		KEY_STATE_RELEASE = 2,
		KEY_STATE_HELD = 3
	};
}
