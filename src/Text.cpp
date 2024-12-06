#include <iostream>
#include <string>
#include <map>

#include "./glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "./Lib.hpp"

#include "./Text.hpp"
#include "./Camera.hpp"
#include "./Scene.hpp"
#include "./Shader.hpp"

Font &Font::load(const char* path)
{
        shader.create("./shaders/textVertexShader.glsl", "./shaders/textFragmentShader.glsl");
        glm::mat4 projection = glm::ortho(0.0f, nitor::scene->camera->width, 0.0f, nitor::scene->camera->height);
        shader.use();
        shader.setMat4("projection", projection);

        FT_Library ft;
        FT_Init_FreeType(&ft);

        FT_Face face;
        FT_New_Face(ft, path, 0, &face);
        FT_Set_Pixel_Sizes(face, 0, 192);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	if (!face)
	{
		std::cout << "Failed to load font file at: " << path << std::endl;
	};

        for (unsigned char c = 0; c < 128; c++)
        {
                FT_Load_Char(face, c, FT_LOAD_RENDER);
                unsigned int texture;
                glGenTextures(1, &texture);
                glBindTexture(GL_TEXTURE_2D, texture);
                glTexImage2D(
                        GL_TEXTURE_2D,
                        0,
                        GL_RED,
                        face->glyph->bitmap.width,
                        face->glyph->bitmap.rows,
                        0,
                        GL_RED,
                        GL_UNSIGNED_BYTE,
                        face->glyph->bitmap.buffer
                );

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                Character character = {
                        texture,
                        glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                        glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                        static_cast<unsigned int>(face->glyph->advance.x)
                };
                Characters.insert(std::pair<char, Character>(c, character));
        };
        glBindTexture(GL_TEXTURE_2D, 0);

        FT_Done_Face(face);
        FT_Done_FreeType(ft);

        glGenVertexArrays(1, &VAO);

	return *this;
};

Text &Text::font(Font *font)
{
	_font = font;
	glGenBuffers(1, &_VBO);
        glBindVertexArray(_font->VAO);
        glBindBuffer(GL_ARRAY_BUFFER, _VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
	return *this;
};

Text &Text::text(std::string text)
{
	_text = text;
	return *this;
};

Text &Text::scale(float scale)
{
	_scale = scale/4.0f;
	return *this;
};

Text &Text::color(float r, float g, float b)
{
	_color = glm::vec3((float)r/255, (float)g/255, (float)b/255);
	return *this;
};

Text &Text::position(float x, float y, float z)
{
	_position = glm::vec3(x*nitor::scene->camera->width/100, y*nitor::scene->camera->width/100, z);
	return *this;
};

Text &Text::draw()
{
	// activate corresponding render state
	_font->shader.use();
	_font->shader.setVec3("color", _color);

	glm::mat4 modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, _position);
	_font->shader.setMat4("modelMatrix", modelMatrix);

	glm::mat4 projection = glm::ortho(0.0f, nitor::scene->camera->width, 0.0f, nitor::scene->camera->height);
	_font->shader.setMat4("projection", projection);

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(_font->VAO);

	// iterate through all characters
	std::string::const_iterator c;

	float x = 0.0f;
	float y = 0.0f;

	for (c = _text.begin(); c != _text.end(); c++)
	{
		Character ch = _font->Characters[*c];

		float xpos = x + ch.bearing.x * _scale;
		float ypos = y - (ch.size.y - ch.bearing.y) * _scale;

		float w = ch.size.x * _scale;
		float h = ch.size.y * _scale;
		// update VBO for each character
		float vertices[6][4] = {
            		{ xpos,     ypos + h,   0.0f, 0.0f },
            		{ xpos,     ypos,       0.0f, 1.0f },
            		{ xpos + w, ypos,       1.0f, 1.0f },

            		{ xpos,     ypos + h,   0.0f, 0.0f },
            		{ xpos + w, ypos,       1.0f, 1.0f },
            		{ xpos + w, ypos + h,   1.0f, 0.0f }
		};
		glBindTexture(GL_TEXTURE_2D, ch.textureID);
		// update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, _VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

        	glBindBuffer(GL_ARRAY_BUFFER, 0);
        	// render quad
        	glDrawArrays(GL_TRIANGLES, 0, 6);
		// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.advance >> 6) * _scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
	};
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	return *this;
};
