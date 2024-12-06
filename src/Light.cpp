#include <iostream>

#include "./glad.h"
#include <GLFW/glfw3.h>

#include "./Light.hpp"
#include "./Mesh.hpp"
#include "./Shader.hpp"
#include "./Vertices.hpp"
#include "./Camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

directionLight &directionLight::create()
{
	_direction = glm::vec3(0.0f, 0.0f, 0.0f);
	_color = glm::vec3(1.0f, 1.0f, 1.0f);

	return *this;
};

directionLight &directionLight::direction(float x, float y, float z)
{
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::rotate(modelMatrix, glm::radians(z), glm::vec3(0.0f, 0.0f, 1.0f));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(y), glm::vec3(0.0f, 1.0f, 0.0f));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(x), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::vec4 dir = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) * modelMatrix;
	_direction = glm::vec3(dir);
	return *this;
};

directionLight &directionLight::color(float r, float g, float b)
{
	_color = _color = glm::vec3((float)r/255, (float)g/255, (float)b/255);;
	return *this;
};

pointLight &pointLight::create()
{
        _position = glm::vec3(0.0f, 0.0f, 0.0f);
        _color = glm::vec3(1.0f, 1.0f, 1.0f);

	mesh.create()
	    .loadGeometry(sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW)
	    .vertexAttribute(0, 3, FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

	shader.create("./shaders/lightVertexShader.glsl", "./shaders/lightFragmentShader.glsl");

        return *this;
};

pointLight &pointLight::position(float x, float y, float z)
{
	_position = glm::vec3(x, y, z);
	mesh.position = _position;

        return *this;
};

pointLight &pointLight::color(float r, float g, float b)
{
        _color = glm::vec3((float)r/255, (float)g/255, (float)b/255);

        return *this;
};

pointLight &pointLight::debugDraw()
{
	shader.setVec3("diffuse", _color);
	mesh.draw(shader);
	return *this;
};
