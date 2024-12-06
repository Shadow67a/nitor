#ifndef SKYBOX_HPP
#define SKYBOX_HPP

#include <string>

#include "./Lib.hpp"
#include "./Shader.hpp"

typedef struct nitor::Skybox
{
	private:
		unsigned int VAO;
		unsigned int VBO;
		unsigned int cubeMap;

		Shader shader;
	public:
		Skybox &load(std::string paths[6]);
		Skybox &draw();
} Skybox;

#endif
