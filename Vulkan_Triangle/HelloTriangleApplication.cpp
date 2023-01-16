#include "HelloTriangleApplication.h"

void HelloTriangleApplication::run()
{
    initVulkan();
    initWindow();
    mainLoop();
    cleanup();
}

void HelloTriangleApplication::initVulkan()
{
}

void HelloTriangleApplication::mainLoop()
{
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
}

void HelloTriangleApplication::cleanup()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void HelloTriangleApplication::initWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    
    window = glfwCreateWindow(WIDTH, HEIGHT, "AMAZING TRIANGLE", nullptr, nullptr);

}
