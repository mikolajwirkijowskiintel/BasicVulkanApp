#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <cstdlib>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 640;

class HelloTriangleApplication {
public:

    void run();

private:
    void initVulkan();

    void mainLoop();

    void cleanup();

    void initWindow();

    /// <summary>
    /// The window that displays our output
    /// </summary>
    GLFWwindow* window;
};