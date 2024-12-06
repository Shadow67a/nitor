#include <iostream>
#include <string>

#include "./glad.h"
#include <GLFW/glfw3.h>

#include "./Lib.hpp"

#include "./Model.hpp"
#include "./Camera.hpp"
#include "./Light.hpp"
#include "./Scene.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "./stb_image.h"

unsigned int nitor::loadTexture(const char* path)
{
	unsigned int textureID;
   	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
        	GLenum format;
		switch (nrComponents)
		{
            		case 1:	format = GL_RED;
				break;
        		case 3:	format = GL_RGB;
				break;
            		case 4:	format = GL_RGBA;
				break;
		};

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
	}
    	else
	{
		std::cout << "[ERROR!]: Failed to load texture at path: " << path << std::endl;
        	stbi_image_free(data);
    	};
	return textureID;
};

Model &Model::create(std::string path, nitor::Shader &shader)
{
	_shader = shader;

	_position = glm::vec3(0.0f, 0.0f, 0.0f);
	_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	_scale = glm::vec3(1.0f, 1.0f, 1.0f);

	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "[ERROR!]: Assimp failed to load model! " << importer.GetErrorString() << std::endl;
	};
	_directory = path.substr(0, path.find_last_of('/'));
	processNode(scene->mRootNode, scene);

	return *this;
};

void Model::processNode(aiNode *node, const aiScene *scene)
{
    // process all the node's meshes (if any)
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; 
        _meshes.push_back(processMesh(mesh, scene));			
    };

    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    };
};


Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
	std::vector<vertex> vertices;
	std::vector<unsigned int> indices;

	for(unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		vertex vertex;

		vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

		if (mesh->mTextureCoords[0])
		{
			vertex.texCoord = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
		} else {
			vertex.texCoord = glm::vec2(0.0f, 0.0f);
		};

		vertices.push_back(vertex);
	};

	for(unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for(unsigned int j = 0; j < face.mNumIndices; j++)
		{
        		indices.push_back(face.mIndices[j]);
		};	
	};

	Mesh resultMesh;
	resultMesh.create(vertices, indices);

	return resultMesh;
};

Model &Model::position(float x, float y, float z)
{
	_position = glm::vec3(x, y, z);
	return *this;
};

Model &Model::rotate(float x, float y, float z)
{
	_rotation = glm::vec3(glm::radians(x), glm::radians(y), glm::radians(z));
	return *this;
};

Model &Model::scale(float x, float y, float z)
{
	_scale = glm::vec3(x, y, z);
	return *this;
};


Model &Model::draw()
{
	_shader.use();

	_modelMatrix = glm::mat4(1.0f);
	_modelMatrix = glm::translate(_modelMatrix, _position);
	_modelMatrix = glm::rotate(_modelMatrix, _rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
        _modelMatrix = glm::rotate(_modelMatrix, _rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
        _modelMatrix = glm::rotate(_modelMatrix, _rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
        _modelMatrix = glm::scale(_modelMatrix, _scale);

	_shader.setMat4("modelMatrix", _modelMatrix)
	       .setMat4("viewMatrix", nitor::scene->camera->view)
	       .setMat4("projectionMatrix", nitor::scene->camera->projection)
	       .setVec3("viewPos", nitor::scene->camera->_position);

	for (unsigned int i = 0; i < nitor::scene->directionLights.size(); i++)
        {
		std::string uniform = "directionLights[].";
        	uniform = uniform.insert(16, std::to_string(i));
                _shader.setVec3((uniform + "direction").c_str(), nitor::scene->directionLights[i]->_direction);
                _shader.setVec3((uniform + "color").c_str(), nitor::scene->directionLights[i]->_color);
        };

	for (unsigned int i = 0; i < nitor::scene->pointLights.size(); i++)
        {
                std::string uniform = "pointLights[].";
                uniform = uniform.insert(12, std::to_string(i));
                _shader.setVec3((uniform + "position").c_str(), nitor::scene->pointLights[i]->_position);
                _shader.setVec3((uniform + "color").c_str(), nitor::scene->pointLights[i]->_color);
        };

	for(unsigned int i = 0; i < _meshes.size(); i++)
	{
		_meshes[i].draw(_shader);
	};
	return *this;
};
