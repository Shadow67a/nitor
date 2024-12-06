#ifndef LIB_HPP
#define LIB_HPP

#include <GLFW/glfw3.h>

#define MAIN_WINDOW 0
#define MOUSE_LEFT false
#define MOUSE_RIGHT true

namespace nitor
{
	extern int init(int width, int height, const char* title);

	extern int createWindow(int width, int height, const char* title, int windowNum);

	extern bool isWindowOpen(int windowNum);

	extern void handleWindows();

	extern GLFWwindow* getCurrentWindow();

	extern void setWindowColor(int r, int g, int b);

	extern void exit();

	extern float getTime();

	extern bool mouseDown(bool button);

	extern void setMouseButtonCallback(void (*callbackFunc)(bool, bool));

	extern void captureMouse();

	extern void enableBlending();

	extern void setAspectRatio(int x, int y);

	extern unsigned int loadTexture(const char* path);

	struct Mesh;
	struct primitiveMesh;
	
	struct Shader;

	struct Camera;

	struct directionLight;
	struct pointLight;

	struct Model;

	struct Triangle;
	struct Rectangle;
	struct Image;

	struct Font;
	struct Text;

	struct Skybox;

	struct Scene;
	extern Scene *scene;

	extern void bindScene(Scene *scene);
};

#endif
