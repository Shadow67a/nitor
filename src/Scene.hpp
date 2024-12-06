#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>

#include "./Lib.hpp"

typedef struct nitor::Scene
{
	nitor::Camera *camera;

	std::vector<nitor::directionLight*> directionLights;
	std::vector<nitor::pointLight*> pointLights;

	nitor::Skybox *skybox = NULL;

	Scene &addCamera(nitor::Camera *camera);	
	Scene &addDirectionLight(nitor::directionLight *light);
	Scene &addPointLight(nitor::pointLight *light);
	Scene &addSkybox(nitor::Skybox *skybox);
	Scene &update();
} Scene;

#endif
