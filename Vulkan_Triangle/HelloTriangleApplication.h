#pragma once
#include <vector>
#include <optional>
#include <functional>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 640;
const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif
 
struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;
	bool isComplete() {
		return graphicsFamily.has_value();
	}
};

class HelloTriangleApplication {
public:

    void run();

   

    static void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

    static VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);

private:
    void initVulkan();

    void createInstance();

    bool checkGLFWLayersSupport();

    std::vector<const char*> getRequiredExtensions();

    void mainLoop();

    void pickPhysicalDevice();

    void setupAppInfo(VkApplicationInfo& appInfo);

    void cleanup();

    void initWindow();

    bool checkValidationLayerSupport();

    template <class Info, class Value, class FReturnType>
    std::vector<Value> getFilledVector(Info info, FReturnType(*func)(Info, uint32_t*, Value*));

    void setupDebugMessenger();

    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

    bool isDeviceSuitable(VkPhysicalDevice device);

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData);

    /// <summary>
    /// The window that displays our output
    /// </summary>
    GLFWwindow* window;
    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
};

template <class Info, class Value, class FReturnType>
std::vector<Value> HelloTriangleApplication::getFilledVector(Info info, FReturnType(*func)(Info, uint32_t*, Value*))
{
    uint32_t count = 0;
    func(info, &count, nullptr);
    std::vector<Value> resultVector(count);
    func(info, &count, resultVector.data());
    return resultVector;
}
