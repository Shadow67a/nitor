#ifndef TEXT_HPP
#define TEXT_HPP

#include <map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "./Lib.hpp"
#include "./Shader.hpp"

struct Character
{
	unsigned int textureID;
	glm::ivec2 size;
	glm::ivec2 bearing;
	unsigned int advance;
};

typedef struct nitor::Font
{
	std::map<GLchar, Character> Characters;
	Shader shader;
	unsigned int VAO;

	Font &load(const char* path);
} Font;

typedef struct nitor::Text
{
	private:
		Font *_font;
		unsigned int _VBO;
		std::string _text;
		glm::vec3 _color;
		float _scale;
		glm::vec3 _position;
	public:
		Text &font(Font *font);
		Text &text(std::string text);
		Text &color(float r, float g, float b);
		Text &scale(float scale);
		Text &position(float x, float y, float z);
		Text &draw();
} Text;

#endif
