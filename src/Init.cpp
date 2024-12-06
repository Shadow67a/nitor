#include <iostream>

#include "./glad.h"
#include <GLFW/glfw3.h>

#include "./Lib.hpp"
#include "./Error.hpp"
#include "./Camera.hpp"
#include "./Scene.hpp"

void (*mouseButtonCallback)(bool, bool);

void framebufferSizeCallback(GLFWwindow*, int width, int height)
{
        glViewport(0, 0, width, height);
	if (nitor::scene != nullptr)
	{
		nitor::scene->camera->width = (float)width;
		nitor::scene->camera->height = (float)height;
	};
};

void mouseButtonProxyCallback(GLFWwindow* window, int button, int action, int mods)
{
	mouseButtonCallback((button==GLFW_MOUSE_BUTTON_RIGHT) ? MOUSE_RIGHT : MOUSE_LEFT, (action==GLFW_PRESS) ? true : false);
};

void nitor::setMouseButtonCallback(void (*callbackFunc)(bool, bool))
{
	mouseButtonCallback = callbackFunc;
	glfwSetMouseButtonCallback(getCurrentWindow(), mouseButtonProxyCallback);
};

int nitor::init(int width, int height, const char* title)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	nitor::createWindow(width, height, title, MAIN_WINDOW);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		nitorError("Failed to initialize glad (openGL)! Perhaps your version is unsupported or there is an issue with your graphics drivers");
		return -1;
	};

	glViewport(0, 0, width, height);

	glEnable(GL_DEPTH_TEST);

	glfwSetFramebufferSizeCallback(getCurrentWindow(), framebufferSizeCallback);

	return 0;
};
