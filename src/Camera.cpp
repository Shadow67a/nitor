#include <iostream>

#include "./Lib.hpp"
#include "./Camera.hpp"

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

float lastFrame;
float currentFrame;
float deltaTime;
double prevX;
double prevY;
double offsetX;
double offsetY;

void mouseMoveCallback(GLFWwindow* window, double x, double y)
{
	offsetX = x - prevX;
	offsetY = prevY - y;

	prevX = x;
	prevY = y;
};

Camera &Camera::create(bool type)
{
	_position = glm::vec3(0.0f, 0.0f, 0.0f);
	_direction = glm::vec3(0.0f, 0.0f, -1.0f);

	_fov = 70.0f;

	_type = type;

	_speed = 0.05f;
	_sensitivity = 0.1f;
	_yaw = 0.0f;
	_pitch = 0.0f;

        this->width = 800.0f;
        this->height = 600.0f;
        this->_position = glm::vec3(0.0f, 0.0f, 0.0f);
        this->view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -1.0f));
        this->projection = glm::perspective(glm::radians(70.0f), this->width / this->height, 0.1f, 100.0f);

	lastFrame = 0.0f;

	glfwSetCursorPosCallback(nitor::getCurrentWindow(), mouseMoveCallback);

	return *this;
};


Camera &Camera::fov(float fov)
{
	_fov = fov;

	float aspect = this->width/this->height;

        if (_type)
        {
                this->projection = glm::perspective(glm::radians(_fov), aspect, 0.1f, 100.0f);
        } else {
                this->projection = glm::ortho(-aspect, aspect, -1.0f, 1.0f, 0.1f, 100.0f);
        };

	return *this;
};

Camera &Camera::position(float x, float y, float z)
{
	_position = glm::vec3(x, y, z);

	return *this;
};

Camera &Camera::direction(float x, float y, float z)
{
	_direction = glm::vec3(x, y, z);
	return *this;
};

Camera &Camera::update()
{
	this->view = glm::lookAt(_position, _position + _direction, glm::vec3(0.0f, 1.0f, 0.0f));

	float aspect = this->width/this->height;

        if (_type)
        {
                this->projection = glm::perspective(glm::radians(_fov), aspect, 0.1f, 100.0f);
        } else {
                this->projection = glm::ortho(-aspect, aspect, -1.0f, 1.0f, 0.1f, 100.0f);
        };
	
	currentFrame = nitor::getTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame; 

	return *this;
};

Camera &Camera::listenInput()
{
	GLFWwindow* window = nitor::getCurrentWindow();

	float speed = _speed * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		_position += speed * _direction;
	};

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
                _position -= speed * _direction;
        };

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
                _position -= speed * glm::normalize(glm::cross(_direction, glm::vec3(0.0f, 1.0f, 0.0f)));
        };

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
                _position += speed * glm::normalize(glm::cross(_direction, glm::vec3(0.0f, 1.0f, 0.0f)));
        };

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
                _position += speed * glm::vec3(0.0f, 1.0f, 0.0f);
        };

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
                _position -= speed * glm::vec3(0.0f, 1.0f, 0.0f);
        };

	offsetX *= _sensitivity;
	offsetY *= _sensitivity;

	_yaw += offsetX;
	_pitch += offsetY;

	if(_pitch > 89.0f)
	{
		_pitch =  89.0f;
	};
	if(_pitch < -89.0f)
	{
		_pitch = -89.0f;
	};

	glm::vec3 direction;
        direction.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
        direction.y = sin(glm::radians(_pitch));
        direction.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));

        _direction = glm::normalize(direction);

	return *this;
};

Camera &Camera::speed(float speed)
{
	_speed = speed;

	return *this;
};
