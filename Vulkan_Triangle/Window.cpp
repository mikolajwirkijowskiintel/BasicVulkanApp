#include "Window.h"
// Default initialization for the window class
Window::Window():WIDTH(800),HEIGHT(640)
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	window = glfwCreateWindow(WIDTH, HEIGHT, "AMAZING TRIANGLE", nullptr, nullptr);


	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
	extensions = new std::vector<const char*>(glfwExtensions, glfwExtensions + glfwExtensionCount);
}

Window::~Window()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

std::vector<const char*>* Window::getVulkanExtensionsRequiredByWindow()
{
	return extensions;
}
