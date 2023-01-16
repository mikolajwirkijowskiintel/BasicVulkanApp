#include "HelloTriangleApplication.h"


void HelloTriangleApplication::run()
{
    
    initWindow();
    initVulkan();
    mainLoop();
    cleanup();
}

void HelloTriangleApplication::initVulkan()
{
    createInstance();
}

void HelloTriangleApplication::createInstance()
{
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Intel";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;
    createInfo.enabledLayerCount = 0;

    VkResult result = vkCreateInstance(&createInfo, nullptr, &instance); 

    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!");
    }
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> extensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

    std::cout << "Requirements met: " << checkGLFWRequirements(glfwExtensions, glfwExtensionCount, extensions);

    
    
}

bool HelloTriangleApplication::checkGLFWRequirements(const char** glfwExtensions,uint32_t glfwExtensionsCount, std::vector<VkExtensionProperties> availableExtensions)
{
    for (int i = 0; i < glfwExtensionsCount; i++) {
        bool matched = false;
        for (const auto& extension : availableExtensions) {
            
            if (glfwExtensions[i] == extension.extensionName) {
                std::cout << glfwExtensions[i] << "," << extension.extensionName << "\n";
                matched = true;
            }
        }
        if (!matched) return false;
        return true;
    }
    return true;
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
