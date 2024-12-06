#ifndef MODEL_HPP
#define MODEL_HPP

#include <vector>
#include <string>

#include "./Lib.hpp"
#include "./Shader.hpp"
#include "./Mesh.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

unsigned int loadTexture(const char *path, const std::string &directory, bool gamma=false);

typedef struct nitor::Model
{
	private:
		std::vector<nitor::Mesh> _meshes;
		std::string _directory;

		void processNode(aiNode *node, const aiScene *scene);
        	nitor::Mesh processMesh(aiMesh *mesh, const aiScene *scene);

		nitor::Shader _shader;

		glm::vec3 _position;
		glm::vec3 _rotation;
		glm::vec3 _scale;

		glm::mat4 _modelMatrix;
	public:
		unsigned int albedo;
		unsigned int metallic;
		unsigned int roughness;

		Model &create(std::string path, nitor::Shader &shader);

		Model &position(float x, float y, float z);
		Model &rotate(float x, float y, float z);
		Model &scale(float x, float y, float z);

		Model &draw();
} Model;

#endif
