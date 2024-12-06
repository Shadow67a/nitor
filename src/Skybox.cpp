#include <iostream>
#include <string>

#include "./glad.h"
#include <GLFW/glfw3.h>

#include "./stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "./Lib.hpp"
#include "./Skybox.hpp"
#include "./Vertices.hpp"
#include "./Camera.hpp"
#include "./Scene.hpp"

Skybox &Skybox::load(std::string paths[6])
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void* )0);

	glGenTextures(1, &cubeMap);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap);

	int width, height, nrChannels;

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for (unsigned int i = 0; i < 6; i++)
	{
		unsigned char* data = stbi_load(paths[i].c_str(), &width, &height, &nrChannels, STBI_rgb);

		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		} else
		{	
			std::cout << "[ERROR!]: Failed to load skybox texture: " << paths[i] << std::endl;
		};
		stbi_image_free(data);

	};

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	shader.create("./shaders/skyboxVertexShader.glsl", "./shaders/skyboxFragmentShader.glsl");

	shader.setInt("skybox", 0);

	return *this;
};

Skybox &Skybox::draw()
{
	glDepthFunc(GL_LEQUAL);

	glm::mat4 view = glm::mat4(glm::mat3(nitor::scene->camera->view));
	shader.setMat4("viewMatrix", view);
	shader.setMat4("projectionMatrix", nitor::scene->camera->projection);
	shader.use();

	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS);

	return *this;
};
