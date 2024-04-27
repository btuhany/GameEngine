#pragma once

#include <stdio.h>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);

	int Initialize();

	GLfloat GetBufferWidth() { return bufferWidth; }
	GLfloat GetBufferHeight() { return bufferHeight; }

	bool GetShouldClose() { return glfwWindowShouldClose(mainWindow); }

	bool* GetKeys() { return keys; }
	GLfloat GetMouseDeltaX();
	GLfloat GetMouseDeltaY();

	void SwapBuffers() { glfwSwapBuffers(mainWindow); }

	~Window();

private:
	GLFWwindow* mainWindow;

	GLint width, height;
	GLint bufferWidth, bufferHeight;

	bool keys[1024]; //covering the ascii characters

	GLfloat mouseLastXPosition = 0;
	GLfloat mouseLastYPosition = 0;
	GLfloat mouseDeltaX = 0;
	GLfloat mouseDeltaY = 0;
	bool mouseFirstMoved = true;

	void createCallbacks();
	static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void handleMouse(GLFWwindow* window, double xPos, double yPos);
};

