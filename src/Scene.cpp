#include <vector>

#include "./Lib.hpp"
#include "./Scene.hpp"
#include "./Light.hpp"
#include "./Camera.hpp"
#include "./Skybox.hpp"

Scene &Scene::addCamera(nitor::Camera *camera)
{
	this->camera = camera;
	return *this;
};

Scene &Scene::addDirectionLight(nitor::directionLight *light)
{
	directionLights.push_back(light);
	return *this;
};

Scene &Scene::addPointLight(nitor::pointLight *light)
{
	pointLights.push_back(light);
	return *this;
};

Scene &Scene::addSkybox(nitor::Skybox *skybox)
{
	this->skybox = skybox;
	return *this;
};

void nitor::bindScene(Scene *scene)
{
	nitor::scene = scene;
};

Scene &Scene::update()
{
        if (camera != nullptr)
	{
		camera->update();
	};

	if (skybox!=NULL)
	{
		skybox->draw();
	};

	return *this;
};
