#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "./Lib.hpp"

#define ORTHOGRAPHIC false
#define PERSPECTIVE true

typedef struct nitor::Camera
{
	private:
		glm::vec3 _direction;

		float _fov;
		bool _type;

		float _speed;
		float _sensitivity;
		float _pitch;
		float _yaw;
	public:
		float width;
                float height;

		glm::vec3 _position;
	        glm::mat4 view;
        	glm::mat4 projection;

		Camera &create(bool type);
		Camera &fov(float fov);
		Camera &position(float x, float y, float z);
		Camera &direction(float x, float y, float z);
		Camera &update();
		Camera &listenInput();
		Camera &speed(float speed);
} Camera;

#endif
