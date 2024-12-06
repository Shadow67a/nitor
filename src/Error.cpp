#include <iostream>
#include <string>

#include "./Error.hpp"

#include "glad.h"
#include <GLFW/glfw3.h>


void nitorGetGLError()
{
	std::cout << glGetError() << std::endl;
};

void nitorError(const char* message)
{
	std::cout << "[ERROR!]: " << message << ";" << std::endl;
};
