#include <iostream>
#include <cmath>
#include <string>

#include "./glad.h"
#include <GLFW/glfw3.h>

#include "./Lib.hpp"

#include "./Elements.hpp"
#include "./Mesh.hpp"
#include "./Shader.hpp"
#include "./Error.hpp"
#include "./Vertices.hpp"
#include "./Camera.hpp"
#include "./Light.hpp"
#include "./Scene.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "./stb_image.h"

Triangle &Triangle::create()
{
	mesh.create()
	    .loadGeometry(sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW)
	    .vertexAttribute(0, 3, FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	_shader.create("./shaders/flatColoredVertexShader.glsl", "./shaders/flatColoredFragmentShader.glsl");

	_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	return *this;
};

Triangle &Triangle::color(int red, int green, int blue, int alpha)
{
	_color = glm::vec4((float)red/255, (float)green/255, (float)blue/255, (float)alpha/255);
	return *this;
};

Triangle &Triangle::position(float x, float y, float z)
{
	mesh.position = glm::vec3(x, y, z);
	return *this;
};

Triangle &Triangle::rotation(float x, float y, float z)
{
	mesh.rotation = glm::vec3(glm::radians(x), glm::radians(y), glm::radians(z));
	return *this;
};

Triangle &Triangle::scale(float x, float y, float z)
{
	mesh.scale = glm::vec3(x, y, z);
	return *this;
};

Triangle &Triangle::draw()
{
	_shader.setVec4("color", _color);

	mesh.draw(_shader);
	return *this;
};

Rectangle &Rectangle::create()
{
	mesh.create()
	    .loadGeometry(sizeof(rectangleVertices), rectangleVertices, GL_STATIC_DRAW)
            .vertexAttribute(0, 3, FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	_shader.create("./shaders/flatColoredVertexShader.glsl", "./shaders/flatColoredFragmentShader.glsl");
	_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

        return *this;
};

Rectangle &Rectangle::color(int red, int green, int blue, int alpha)
{
        _color = glm::vec4((float)red/255, (float)green/255, (float)blue/255, (float)alpha/255);
        return *this;
};

Rectangle &Rectangle::position(float x, float y, float z)
{
        mesh.position = glm::vec3(x, y, z);
        return *this;
};

Rectangle &Rectangle::rotation(float x, float y, float z)
{
        mesh.rotation = glm::vec3(glm::radians(x), glm::radians(y), glm::radians(z));
        return *this;
};

Rectangle &Rectangle::scale(float x, float y, float z)
{
        mesh.scale = glm::vec3(x, y, z);
        return *this;
};

Rectangle &Rectangle::draw()
{
        _shader.setVec4("color", _color);
	mesh.draw(_shader);
        return *this;
};

Image &Image::create(const char* imagePath)
{
        mesh.create()
	    .loadGeometry(sizeof(imageVertexData), imageVertexData, GL_STATIC_DRAW)
            .vertexAttribute(0, 3, FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0)
	    .vertexAttribute(1, 2, FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)) );

	_shader.create("./shaders/flatTexturedVertexShader.glsl", "./shaders/flatTexturedFragmentShader.glsl");

	stbi_set_flip_vertically_on_load(true);
        imageData = stbi_load(imagePath, &width, &height, &nrChannels, STBI_rgb);

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        if (imageData)
        {
                glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
                glGenerateMipmap(GL_TEXTURE_2D);
        } else {
                std::cout << "[ERROR!]: Failed to load image: " << imagePath << std::endl;
        };

        stbi_image_free(imageData);
        _textureUnit = 0;
        _uniformSampler = "imageTexture";

        return *this;
};

Image &Image::draw()
{
	_shader.setInt(_uniformSampler, _textureUnit);
        glActiveTexture(GL_TEXTURE0 + _textureUnit);
        glBindTexture(GL_TEXTURE_2D, texture);

	mesh.draw(_shader);

        return *this;
};

Image &Image::filter(bool filter)
{
	if (filter)
        {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        } else {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        };

	return *this;
};

Image &Image::position(float x, float y, float z)
{
        mesh.position = glm::vec3(x, y, z);
        return *this;
};

Image &Image::rotation(float x, float y, float z)
{
        mesh.rotation = glm::vec3(glm::radians(x), glm::radians(y), glm::radians(z));
        return *this;
};

Image &Image::scale(float x, float y, float z)
{
        mesh.scale = glm::vec3(x, y, z);
        return *this;
};
