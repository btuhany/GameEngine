#pragma once

#include <stdio.h>

#include <GL\glew.h>
#include <GLFW\glfw3.h>
namespace GameEngine {
	class Window
	{
	public:
		Window();
		Window(GLint windowWidth, GLint windowHeight);

		int Initialize();

		GLfloat GetBufferWidth() { return m_BufferWidth; }
		GLfloat GetBufferHeight() { return m_BufferHeight; }

		bool GetShouldClose() { return glfwWindowShouldClose(m_glWindow); }

		bool* GetKeys() { return m_Keys; }
		GLfloat GetMouseDeltaX();
		GLfloat GetMouseDeltaY();

		void SwapBuffers() { glfwSwapBuffers(m_glWindow); }

		~Window();

	private:
		GLFWwindow* m_glWindow;

		GLint m_Width, m_Height;
		GLint m_BufferWidth, m_BufferHeight;

		bool m_Keys[1024]; //covering the ascii characters

		GLfloat m_MouseLastXPosition = 0;
		GLfloat m_MouseLastYPosition = 0;
		GLfloat m_MouseDeltaX = 0;
		GLfloat m_MouseDeltaY = 0;
		bool m_MouseFirstMoved = true;

		void createCallbacks();
		static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
		static void handleMouse(GLFWwindow* window, double xPos, double yPos);
	};
}
