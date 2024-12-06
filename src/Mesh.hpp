#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
#include <string>

#include "./Lib.hpp"
#include "./Shader.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define FLOAT GL_FLOAT

struct vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
};

typedef struct nitor::Mesh
{
	private:
		unsigned int VAO, VBO, EBO;
	public:
		std::vector<vertex> _vertices;
		std::vector<unsigned int> _indices;

		Mesh &create(std::vector<vertex> &vertices, std::vector<unsigned int> &indices);

		Mesh &draw(Shader &shader);
} Mesh;

typedef struct nitor::primitiveMesh
{
	unsigned int _vertexBuffer;
	unsigned int _VAO;
	unsigned int _size;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::mat4 _modelMatrix;	

	primitiveMesh &create();
	primitiveMesh &loadGeometry(int size, const void* data, GLenum usage);
	primitiveMesh &vertexAttribute(int layout, int count, GLenum type, bool normalized, unsigned int stride, const void* offset);
	primitiveMesh &use();
	primitiveMesh &draw(nitor::Shader &shader);

} primitiveMesh;

#endif
