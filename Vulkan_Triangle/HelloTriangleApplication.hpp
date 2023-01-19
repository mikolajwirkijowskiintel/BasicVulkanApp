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
	/// <summary>
	/// Checks if all members of the struct are initialized
	/// </summary>
	/// <returns></returns>
	bool isComplete() {
		return graphicsFamily.has_value();
	}
};

class HelloTriangleApplication {
public:

    void run();

   

private:
    /// static functions
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData);

	static void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

	static VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);

    void initVulkan();

    void initWindow();

    void createLogicalDevice();

    void cleanup();

    void pickPhysicalDevice();

    void mainLoop();

    void createInstance();

    bool checkGLFWLayersSupport();

    std::vector<const char*> getRequiredExtensions();

    bool checkValidationLayerSupport();

    template <class Info, class Value, class FReturnType>
    std::vector<Value> getFilledVector(Info info, FReturnType(*func)(Info, uint32_t*, Value*));

    void setupAppInfo(VkApplicationInfo& appInfo);

    void setupDebugMessenger();

    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

    bool isDeviceSuitable(VkPhysicalDevice device);

   

    GLFWwindow* window;
    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
    VkPhysicalDevice physicalDevice;
    VkDevice device;
    VkQueue graphicsQueue;
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
