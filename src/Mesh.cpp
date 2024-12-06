#include <string>
#include <vector>

#include "./glad.h"
#include "GLFW/glfw3.h"

#include "./Lib.hpp"

#include "./Mesh.hpp"
#include "./Shader.hpp"
#include "./Camera.hpp"
#include "./Scene.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

primitiveMesh &primitiveMesh::create()
{
	glGenBuffers(1, &_vertexBuffer);
	glGenVertexArrays(1, &_VAO);
	_modelMatrix = glm::mat4(1.0f);
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);

	return *this;
};

primitiveMesh &primitiveMesh::loadGeometry(int size, const void* data, GLenum usage)
{
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);
	_size = size/sizeof(float);

	return *this;
};

primitiveMesh &primitiveMesh::vertexAttribute(int layout, int count, GLenum type, bool normalized, unsigned int stride, const void* offset)
{
	glBindVertexArray(_VAO);
	glVertexAttribPointer(layout, count, type, normalized, stride, offset);
	glEnableVertexAttribArray(layout);

	return *this;
};

primitiveMesh &primitiveMesh::use()
{
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	return *this;
};

primitiveMesh &primitiveMesh::draw(Shader &shader)
{
	shader.use();

	_modelMatrix = glm::mat4(1.0f);
	_modelMatrix = glm::translate(_modelMatrix, position);
	_modelMatrix = glm::rotate(_modelMatrix, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	_modelMatrix = glm::rotate(_modelMatrix, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	_modelMatrix = glm::rotate(_modelMatrix, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	_modelMatrix = glm::scale(_modelMatrix, scale);

	shader.setMat4("modelMatrix", _modelMatrix);
	shader.setMat4("viewMatrix", nitor::scene->camera->view);
	shader.setMat4("projectionMatrix", nitor::scene->camera->projection);

	glBindVertexArray(_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glDrawArrays(GL_TRIANGLES, 0, _size);

	return *this;
};

Mesh &Mesh::create(std::vector<vertex> &vertices, std::vector<unsigned int> &indices)
{
	_vertices = vertices;
	_indices = indices;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, texCoord));
	glBindVertexArray(0);

	return *this;
};

Mesh &Mesh::draw(nitor::Shader &shader)
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0 );
	glBindVertexArray(0);

	return *this;
};
