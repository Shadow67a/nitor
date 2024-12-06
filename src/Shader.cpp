#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "./glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "./Shader.hpp"
#include "./Error.hpp"

Shader &Shader::create(const char* vShaderPath, const char* fShaderPath)
{


	std::string vertexCode;
    	std::string fragmentCode;
    	std::ifstream vShaderFile;
    	std::ifstream fShaderFile;
    
	vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    	fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    
	try 
    	{
        	vShaderFile.open(vShaderPath);
        	fShaderFile.open(fShaderPath);
        	std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		vShaderFile.close();
		fShaderFile.close();

		vertexCode   = vShaderStream.str();
        	fragmentCode = fShaderStream.str();		
    	}
    	catch(std::ifstream::failure e)
    	{
        	nitorError("Unable to read shader files!");
    	}


	vertexShaderSource = vertexCode.c_str();
	fragmentShaderSource = fragmentCode.c_str();

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

		
	glCompileShader(vertexShader);

	int success;
	char log[512];

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, log);
		std::cout << "[ERROR!]: Could not compile vertex shader! " << log << std::endl;
	return *this; };


	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
        {
		glGetShaderInfoLog(fragmentShader, 512, NULL, log);
		std::cout << "[ERROR!]: Could not compile fragment shader! " << log << std::endl;
	return *this; };

	program = glCreateProgram();

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return *this;
};

Shader &Shader::use()
{
	glUseProgram(program);
	return *this;
};

Shader &Shader::setInt(const char* uniform, int value)
{
	glProgramUniform1i(program, glGetUniformLocation(program, uniform), value);
	return *this;
};

Shader &Shader::setFloat(const char* uniform, float &value)
{
	glProgramUniform1f(program, glGetUniformLocation(program, uniform), value);
	return *this;
};

Shader &Shader::setVec3(const char* uniform, glm::vec3 &value)
{
	glProgramUniform3fv(program, glGetUniformLocation(program, uniform), 1, glm::value_ptr(value));
	return *this;
};

Shader &Shader::setVec4(const char* uniform, glm::vec4 &value)
{
	glProgramUniform4fv(program, glGetUniformLocation(program, uniform), 1, glm::value_ptr(value));
	return *this;
};

Shader &Shader::setMat4(const char* uniform, glm::mat4 &value)
{
	glProgramUniformMatrix4fv(program, glGetUniformLocation(program, uniform), 1, GL_FALSE, glm::value_ptr(value));
	return *this;
};

