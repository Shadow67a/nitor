#include "../include/nitor.hpp"

int main()
{
	nitor::init(800, 600, "clock");
	nitor::setWindowColor(0, 0, 0);
	nitor::enableBlending();

	nitor::Scene scene;
	nitor::bindScene(&scene);
	nitor::Camera camera;
	camera.position(0.0, 0.0, -1.0);
	scene.addCamera(&camera);

	nitor::Font SanFrancisco;
	SanFrancisco.load("./assets/SFProBold.otf");
	nitor::Text text;
	text.font(&SanFrancisco)
	    .color(255, 255, 255)
	    .scale(1.0)
	    .position(2.0, 50.0, 0.0)
	    .text("SanFrancisco");

	while (nitor::isWindowOpen(MAIN_WINDOW))
	{
		camera.update();
		text.draw();
		nitor::handleWindows();
	};

	nitor::exit();
	return 0;
};
