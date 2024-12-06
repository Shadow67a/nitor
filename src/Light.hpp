#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "./Lib.hpp"
#include "./Mesh.hpp"
#include "./Shader.hpp"

typedef struct nitor::directionLight
{
	public:
		glm::vec3 _direction;

                glm::vec3 _color;

		directionLight &create();
		directionLight &direction(float x, float y, float z);

		directionLight &color(float r, float g, float b);

} directionLight;

typedef struct nitor::pointLight
{
        private:
		primitiveMesh mesh;
		Shader shader;
        public:
		glm::vec3 _position;

                glm::vec3 _color;

                pointLight &create();
                pointLight &position(float x, float y, float z);

		pointLight &color(float r, float g, float b);

		pointLight &debugDraw();
} pointLight;

#endif
