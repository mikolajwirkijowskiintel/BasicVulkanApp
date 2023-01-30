#include "RenderEngine.h"
#include <cstdlib>

int main() {
	RenderEngine* app = new RenderEngine();
	app->run();
	delete app;
	return EXIT_SUCCESS;
}