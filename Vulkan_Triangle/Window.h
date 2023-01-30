#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <Vector>

class Window
{

public:
	Window();
	~Window();


	// getters
	GLFWwindow* getWindow() const { return window; }
	std::vector<const char*>* getVulkanExtensionsRequiredByWindow();
	

private:
	GLFWwindow* window;
	const uint32_t WIDTH;
	const uint32_t HEIGHT;
	std::vector<const char*>* extensions;

};

