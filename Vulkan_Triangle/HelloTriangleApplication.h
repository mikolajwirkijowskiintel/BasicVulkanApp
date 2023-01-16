#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <iostream>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 640;

class HelloTriangleApplication {
public:

    void run();

private:
    void initVulkan();

    void createInstance();

    bool checkGLFWRequirements(const char** glfwExtensions, uint32_t glfwExtensionsCount, std::vector<VkExtensionProperties> availableExtensions);

    void mainLoop();

    void cleanup();

    void initWindow();

    /// <summary>
    /// The window that displays our output
    /// </summary>
    GLFWwindow* window;
    VkInstance instance;
};