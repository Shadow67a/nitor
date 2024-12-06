#ifndef SHADER_HPP
#define SHADER_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "./Lib.hpp"

typedef struct nitor::Shader
{
        unsigned int vertexShader;
        const char* vertexShaderSource;

        unsigned int fragmentShader;
        const char* fragmentShaderSource;

        unsigned int program;

	Shader &create(const char* vShaderPath, const char* fShaderPath);

	Shader &use();

	Shader &setInt(const char* uniform, int value);
	Shader &setFloat(const char* uniform, float &value);
	Shader &setVec3(const char* uniform, glm::vec3 &value);
	Shader &setVec4(const char* uniform, glm::vec4 &value);
	Shader &setMat4(const char* uniform, glm::mat4 &value);

} Shader;

#endif
