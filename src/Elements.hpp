#ifndef ELEMENTS_HPP
#define ELEMENTS_HPP

#include "./Lib.hpp"
#include "./Mesh.hpp"
#include "./Shader.hpp"
#include "./Vertices.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

typedef struct nitor::Triangle
{
	private:
		nitor::Shader _shader;
		glm::vec4 _color;
	public:
		nitor::primitiveMesh mesh;
		Triangle &create();

		Triangle &color(int red, int green, int blue, int alpha);

		Triangle &position(float x, float y, float z);
		Triangle &rotation(float x, float y, float z);
		Triangle &scale(float x, float y, float z);

		Triangle &draw();
} Triangle;

typedef struct nitor::Rectangle
{
	private:
		nitor::Shader _shader;
        	glm::vec4 _color;
	public:
		nitor::primitiveMesh mesh;
        	Rectangle &create();

        	Rectangle &color(int red, int green, int blue, int alpha);

		Rectangle &position(float x, float y, float z);
		Rectangle &rotation(float x, float y, float z);
		Rectangle &scale(float x, float y, float z);

        	Rectangle &draw();
} Rectangle;

typedef struct nitor::Image
{
	private:
		nitor::Shader _shader;
		int width;
		int height;
		int nrChannels;

		unsigned char* imageData;
		const char* _uniformSampler;
		unsigned int texture;
		unsigned int _textureUnit;
	public:
		nitor::primitiveMesh mesh;
		Image &create(const char* imagePath);

		Image &filter(bool filter);

		Image &position(float x, float y, float z);
                Image &rotation(float x, float y, float z);
                Image &scale(float x, float y, float z);

		Image &draw();
} Image;

#endif
