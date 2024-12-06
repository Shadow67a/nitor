#include <iostream>

#include "./glad.h"
#include <GLFW/glfw3.h>

#include "./Lib.hpp"
#include "./Scene.hpp"
#include "./Camera.hpp"
#include "./Light.hpp"

GLFWwindow* windows[1];
int currentWindow;

Scene *nitor::scene;

int nitor::createWindow(int width, int height, const char* title, int windowNum)
{
	windows[windowNum] = glfwCreateWindow(width, height, title, NULL, NULL);

	if (windows[windowNum] == NULL)
	{
		std::cout << "[ERROR!]: Could not open window titled " << title << std::endl;
		glfwTerminate();
		return -1;
	};

	glfwMakeContextCurrent(windows[windowNum]);
	currentWindow = windowNum;
	nitor::scene = nullptr;
	return 0;
};

bool nitor::isWindowOpen(int windowNum)
{
	return !glfwWindowShouldClose(windows[windowNum]);
};

void nitor::handleWindows()
{
	if (nitor::scene != nullptr)
	{
		nitor::scene->update();
	};

	glfwSwapBuffers(windows[currentWindow]);
	glfwPollEvents();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
};

GLFWwindow* nitor::getCurrentWindow()
{
	return windows[currentWindow];
};

void nitor::setWindowColor(int r, int g, int b)
{
	glClearColor((float)r/255, (float)g/255, (float)b/255, 1.0f);
};

void nitor::exit()
{
	glfwTerminate();
};

float nitor::getTime()
{
	return (float)glfwGetTime();
};

bool nitor::mouseDown(bool button)
{
	return glfwGetMouseButton(windows[currentWindow], (button) ? GLFW_MOUSE_BUTTON_RIGHT : GLFW_MOUSE_BUTTON_LEFT);
};

void nitor::captureMouse()
{
	glfwSetInputMode(windows[currentWindow], GLFW_CURSOR, GLFW_CURSOR_DISABLED);
};

void nitor::enableBlending()
{
	glEnable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
};

void nitor::setAspectRatio(int x, int y)
{
	glfwSetWindowAspectRatio(windows[currentWindow], 16, 9);
};
